package heinemann.photostreams;

import android.content.ContentResolver;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.PersistableBundle;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v4.content.FileProvider;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import org.json.JSONException;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import hochschuledarmstadt.photostream_tools.BitmapUtils;
import hochschuledarmstadt.photostream_tools.IPhotoStreamClient;
import hochschuledarmstadt.photostream_tools.PhotoStreamActivity;
import hochschuledarmstadt.photostream_tools.callback.OnPhotoUploadListener;
import hochschuledarmstadt.photostream_tools.model.HttpError;
import hochschuledarmstadt.photostream_tools.model.Photo;

import static heinemann.photostreams.MainActivity.REQUEST_TAKE_PHOTO;
import static heinemann.photostreams.MainActivity.picture;
import static heinemann.photostreams.MainActivity.image;
/**
 * Created by root on 22.11.17.
 */

public class PhotoUpload extends PhotoStreamActivity implements OnPhotoUploadListener {

Button gal;
    Button UP;


EditText desc;
ImageView myimage;

    private static final String TAG = PhotoUpload.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        Log.d(TAG, "onCreate()");

        setContentView(R.layout.photo_up);
        desc = (EditText) findViewById(R.id.textdesc);
        myimage = (ImageView)findViewById(R.id.myimage);
        myimage.setImageBitmap(image);
        UP = (Button) findViewById(R.id.up);
        UP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                IPhotoStreamClient photoStreamClient = getPhotoStreamClient();
                String d = String.valueOf(desc.getText());
                try {
                    photoStreamClient.uploadPhoto(picture, d);
                    myimage.setVisibility(View.INVISIBLE);
                    desc.setVisibility(View.INVISIBLE);

                } catch (IOException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                Toast.makeText(PhotoUpload.this, "Photo Uploaded", Toast.LENGTH_SHORT).show();
            }
        });





    }
    /*private static int RESULT_LOAD_IMAGE = 1;

    void openGallery(){
        Intent i = new Intent(Intent.ACTION_PICK,android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(i,RESULT_LOAD_IMAGE);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        Uri   imageUri = data.getData();;
        //= (Uri) data.getParcelableExtra(Intent.EXTRA_STREAM);
            //Do whatever that you desire here. or leave this blank

        this.getContentResolver().notifyChange(imageUri, null);
        ContentResolver cr = this.getContentResolver();
        try {
            image = android.provider.MediaStore.Images.Media.getBitmap(cr, imageUri);

        } catch (Exception e) {
            Toast.makeText(this, "Failed to load", Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Failed to load", e);
        }

        if(image!=null) {
            picture = BitmapUtils.bitmapToBytes(image);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }
*/
    @Override
    protected void onPhotoStreamServiceConnected(IPhotoStreamClient photoStreamClient, Bundle savedInstanceState) {

    }

    @Override
    protected void onPhotoStreamServiceDisconnected(IPhotoStreamClient photoStreamClient) {

    }

    @Override
    public void onPhotoUploaded(Photo photo) {
        Toast.makeText(this, "Photo Uploaded", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onPhotoUploadFailed(HttpError httpError) {
        Toast.makeText(this, "Photo NotUploaded", Toast.LENGTH_LONG).show();

    }

}
