package heinemann.photostreams;

import android.os.Bundle;

import heinemann.photostreams.R;
import hochschuledarmstadt.photostream_tools.IPhotoStreamClient;
import hochschuledarmstadt.photostream_tools.PhotoStreamActivity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import android.view.View;
import android.widget.Button;

import com.google.gson.Gson;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;

import hochschuledarmstadt.photostream_tools.model.Photo;

/**
 * Created by root on 08.12.17.
 */

public class NotificationActivity extends PhotoStreamActivity {





    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Layout erzeugen
        setContentView(R.layout.activity_notification);
        // Button referenzieren
        Button button = (Button) findViewById(R.id.intent_button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    Photo photo = loadFakePhoto();
                    // Wenn auf den Button geklickt wurde
                    Intent intent = new Intent(IPhotoStreamClient.INTENT_ACTION_NEW_PHOTO_AVAILABLE);
                    // dann einen Broadcast an das System senden.
                    intent.putExtra(IPhotoStreamClient.INTENT_KEY_PHOTO, photo);
                    sendBroadcast(intent);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (NoSuchFieldException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private Photo loadFakePhoto() throws IOException, NoSuchFieldException, IllegalAccessException {
        InputStream is = getAssets().open("architecture.png");
        Bitmap bitmap = BitmapFactory.decodeStream(is);
        File file = new File(getExternalCacheDir(), "1.png");
        bitmap.compress(Bitmap.CompressFormat.JPEG, 20, new FileOutputStream(file));
        Photo photo = new Gson().fromJson("{\"photo_id\":1,\"comment\":\"Photostream Architektur\",\"deleteable\":false,\"comment_count\":0,\"favorite\":0}", Photo.class);
        Field f = Photo.class.getDeclaredField("imageFilePath");
        f.setAccessible(true);
        f.set(photo, file.getAbsolutePath());
        return photo;
    }













    @Override
    protected void onPhotoStreamServiceConnected(IPhotoStreamClient photoStreamClient, Bundle savedInstanceState) {

    }

    @Override
    protected void onPhotoStreamServiceDisconnected(IPhotoStreamClient photoStreamClient) {

    }
}
