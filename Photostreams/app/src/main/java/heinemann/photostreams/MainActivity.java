package heinemann.photostreams;

import hochschuledarmstadt.photostream_tools.BitmapUtils;

import android.content.ContentResolver;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.PersistableBundle;
import android.provider.MediaStore;
import android.support.v4.content.FileProvider;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import hochschuledarmstadt.photostream_tools.IPhotoStreamClient;
import hochschuledarmstadt.photostream_tools.PhotoStreamActivity;
import hochschuledarmstadt.photostream_tools.RequestType;
import hochschuledarmstadt.photostream_tools.adapter.BasePhotoAdapter;
import hochschuledarmstadt.photostream_tools.callback.OnNewPhotoReceivedListener;
import hochschuledarmstadt.photostream_tools.callback.OnPhotoDeletedListener;
import hochschuledarmstadt.photostream_tools.callback.OnPhotoFavoredListener;
import hochschuledarmstadt.photostream_tools.callback.OnPhotosReceivedListener;
import hochschuledarmstadt.photostream_tools.callback.OnRequestListener;
import hochschuledarmstadt.photostream_tools.model.HttpError;
import hochschuledarmstadt.photostream_tools.model.Photo;
import hochschuledarmstadt.photostream_tools.model.PhotoQueryResult;


public class MainActivity extends PhotoStreamActivity implements OnRequestListener,
        OnPhotosReceivedListener, OnNewPhotoReceivedListener,
        OnPhotoDeletedListener, OnPhotoFavoredListener, View.OnClickListener {
    public static int PHOTO_ID;
    private static final String TAG1 = PhotoUpload.class.getName();
    static public int pic_ID;
    public static Bitmap image;
    ImageButton del_btn;
    ImageButton Notifi_btn;
    ImageButton Cam_btn;
    ImageButton gallery;
    ImageButton up_btn;
    public static byte[] picture;
    private static final String TAGo = MainActivity.class.getName();
    private Button loadMoreButton;


    RecyclerView myRecyclerView;
    RecyclerView.LayoutManager myLayoutManager;

    private PhotoAdapter adapter = new PhotoAdapter(this);
    private boolean check = false;
    private boolean isnotfav = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG1, "onCreate()");


        setContentView(R.layout.activity_main);


        myRecyclerView = (RecyclerView) findViewById(R.id.recycler);
        myLayoutManager = new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false);
        myRecyclerView.setLayoutManager(myLayoutManager);


        // Als Letztes der RecyclerView den Adapter als Datenquelle zuweisen
        myRecyclerView.setAdapter(adapter);
        Notifi_btn = (ImageButton) findViewById(R.id.Fav_btn);
        Cam_btn = (ImageButton) findViewById(R.id.cam_btn);
        up_btn = (ImageButton) findViewById(R.id.Upbtn);
        gallery = (ImageButton) findViewById(R.id.gallery);
        Notifi_btn.setImageResource(R.drawable.bell);
        Cam_btn.setImageResource(R.drawable.cam);

        loadMoreButton = (Button) findViewById(R.id.button);
        loadMoreButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
              //  loadMoreButton.setEnabled(false);
                IPhotoStreamClient photoStreamClient = getPhotoStreamClient();
                // Wenn nicht bereits ein Request für Photos ausgeführt wird,
                if (!photoStreamClient.hasOpenRequestOfType(RequestType.LOAD_PHOTOS)) {
                    // dann nächste Seite aus dem Stream laden
                    photoStreamClient.loadMorePhotos();

                }
            }

        });

        // del_btn.setImageResource(R.drawable.trash);

        Cam_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                dispatchTakePictureIntent();
            }


        });

        gallery.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openGallery();
            }
        });
        up_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendMessage();
            }
        });

        adapter.setOnItemClickListener(R.id.imageView, new BasePhotoAdapter.OnItemClickListener<PhotoAdapter.PhotoViewHolder>() {
            @Override
            public void onItemClicked(PhotoAdapter.PhotoViewHolder viewHolder, View v, Photo photo) {
                String desc = photo.getDescription();
                Toast.makeText(MainActivity.this, desc, Toast.LENGTH_SHORT).show();
                pic_ID = photo.getId();
                // getPhotoStreamClient().loadMorePhotos();

            }
        });


    }





    private static int RESULT_LOAD_IMAGE = 1;

    void openGallery() {
        Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(i, RESULT_LOAD_IMAGE);
    }


    public void sendMessage() {
        Intent intent = new Intent(MainActivity.this, PhotoUpload.class);
        startActivity(intent);
    }

    public void sendMessagetonetify(View view) {
        Intent intent = new Intent(MainActivity.this, NotificationActivity.class);
        startActivity(intent);
    }


    @Override
    protected void onPhotoStreamServiceConnected(IPhotoStreamClient photoStreamClient, Bundle savedInstanceState) {
        photoStreamClient.loadPhotos();



        photoStreamClient.addOnPhotosReceivedListener(this);

        photoStreamClient.addOnPhotoDeletedListener(this);
        photoStreamClient.addOnNewPhotoReceivedListener(this);


    }


    @Override
    protected void onPhotoStreamServiceDisconnected(IPhotoStreamClient photoStreamClient) {
        photoStreamClient.removeOnNewPhotoReceivedListener(this);
        photoStreamClient.removeOnPhotosReceivedListener(this);
    }


    @Override
    public void onRequestStarted() {


    }

    @Override
    public void onRequestFinished() {

    }


    @Override
    public void onPhotosReceived(PhotoQueryResult result) {
        List<Photo> photos = result.getPhotos();
        if (result.isFirstPage()) {
            // Zum ersten Mal abgerufen oder Aktualisierung des Streams wurde explizit angefordet => Photos ersetzen
            adapter.set(photos);

        } else {
            // Photos an die Liste anhängen
            adapter.addAll(photos);

        }
        // Request ist beendet, also kann der Button wieder aktiviert werden

        // Den Button sichtbar machen, wenn weitere Seiten im Stream vorhanden sind, ansonsten ausblenden


    }


    @Override
    public void onReceivePhotosFailed(HttpError httpError) {
        String title = "Could not load photos";
        // Fehler anzeigen in einem AlertDialog
        Utils.showErrorInAlertDialog(this, title, httpError);
        // Request ist beendet, also kann der Button wieder aktiviert werden
        loadMoreButton.setEnabled(true);
    }

    @Override
    public void onNoNewPhotosAvailable() {

getPhotoStreamClient().loadMorePhotos();
    }


    @Override
    public void onNewPhotoReceived(Photo photo) {
        adapter.addAtFront(photo);
        //adapter.re

    }


    String mCurrentPhotoPath;

    private File createImageFile() throws IOException {
        // Create an image file name
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String imageFileName = "JPEG_" + timeStamp + "_";
        File storageDir = getExternalFilesDir(Environment.DIRECTORY_PICTURES);
        File image = File.createTempFile(
                imageFileName,  /* prefix */
                ".jpg",         /* suffix */
                storageDir      /* directory */
        );

        // Save a file: path for use with ACTION_VIEW intents
        mCurrentPhotoPath = image.getAbsolutePath();
        return image;
    }


    static final int REQUEST_TAKE_PHOTO = 2;
    Uri photoURI;

    void dispatchTakePictureIntent() {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        // Ensure that there's a camera activity to handle the intent
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            // Create the File where the photo should go
            File photoFile = null;
            try {
                photoFile = createImageFile();
            } catch (IOException ex) {
                // Error occurred while creating the File

            }
            // Continue only if the File was successfully created
            if (photoFile != null) {
                photoURI = FileProvider.getUriForFile(this,
                        "com.example.android.fileprovider",
                        photoFile);
                takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, photoURI);
                startActivityForResult(takePictureIntent, REQUEST_TAKE_PHOTO);
            }
        }

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RESULT_LOAD_IMAGE) {
            Uri imageUri = data.getData();
            ;
            //= (Uri) data.getParcelableExtra(Intent.EXTRA_STREAM);
            //Do whatever that you desire here. or leave this blank

            this.getContentResolver().notifyChange(imageUri, null);
            ContentResolver cr = this.getContentResolver();
            try {
                image = android.provider.MediaStore.Images.Media.getBitmap(cr, imageUri);

            } catch (Exception e) {
                Toast.makeText(this, "Failed to load", Toast.LENGTH_SHORT).show();
                Log.d(TAGo, "Failed to load", e);
            }

            if (image != null) {
                picture = BitmapUtils.bitmapToBytes(image);
            }
        } else if (requestCode == REQUEST_TAKE_PHOTO) {
            this.getContentResolver().notifyChange(photoURI, null);
            ContentResolver cr = this.getContentResolver();
            try {
                image = android.provider.MediaStore.Images.Media.getBitmap(cr, photoURI);

            } catch (Exception e) {
                Toast.makeText(this, "Failed to load", Toast.LENGTH_SHORT).show();
                Log.d(TAG1, "Failed to load", e);
            }//todo

            if (image != null) {
                picture = BitmapUtils.bitmapToBytes(image);
            }
        }


        super.onActivityResult(requestCode, resultCode, data);

        Toast.makeText(MainActivity.this, "to upload click on the uplaod button ", Toast.LENGTH_SHORT).show();


    }


    @Override
    public void onPhotoDeleted(int photoId) {

        Toast.makeText(this, "Deleted", Toast.LENGTH_SHORT).show();

    }

    @Override
    public void onPhotoDeleteFailed(int photoId, HttpError httpError) {

    }


    @Override
    public void onPhotoFavored(int photoId) {
        // Toast.makeText(this, "Hinzugefuegt", Toast.LENGTH_SHORT).show();
        adapter.favorPhoto(photoId);
        adapter.notifyDataSetChanged();
    }

    @Override
    public void onPhotoUnfavored(int photoId) {
        Toast.makeText(this, "favorite", Toast.LENGTH_SHORT).show();

    }

    @Override
    public void onFavoringPhotoFailed(int photoId, HttpError httpError) {
        Toast.makeText(this, "fehler", Toast.LENGTH_SHORT).show();

    }


    public void sendMessagetoComments(View view) {
        Intent intent = new Intent(MainActivity.this, CommentActivity.class);
        startActivity(intent);
    }

    @Override
    public void onClick(View view) {
        // can get the id of pic from here for comments
        // PhotoAdapter.PhotoViewHolder holder = new PhotoAdapter.PhotoViewHolder(vieww);

        switch (view.getId()) {
            case R.id.favourite: {
                Photo p = (Photo) view.getTag();
                if (!p.isFavorite()) {

                   getPhotoStreamClient().favoritePhoto(p.getId());
                    getPhotoStreamClient().loadPhotos();


                } else {
                    getPhotoStreamClient().unfavoritePhoto(p.getId());
                    getPhotoStreamClient().loadPhotos();
                }



            }
            break;
            case R.id.mycomment: {
                Photo p = (Photo) view.getTag();
                PHOTO_ID = p.getId();
                sendMessagetoComments(view);
            }
            break;
            case R.id.deleteimg: {
                Photo p = (Photo) view.getTag();
                PHOTO_ID = p.getId();
                {
                    IPhotoStreamClient myIPhotoStreamClient = getPhotoStreamClient();

                    if (p.isDeleteable()) {
                        myIPhotoStreamClient.deletePhoto(PHOTO_ID);
                        adapter.remove(PHOTO_ID);

                    } else {
                        Toast.makeText(this, " Not authorised ", Toast.LENGTH_SHORT).show();

                    }
                    getPhotoStreamClient().loadMorePhotos();
                }
            }
        }


    }
}
