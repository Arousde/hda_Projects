package heinemann.photostreams;

import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.support.v4.app.NotificationCompat;
import android.widget.Toast;

import hochschuledarmstadt.photostream_tools.IPhotoStreamClient;
import hochschuledarmstadt.photostream_tools.model.Photo;





import static android.content.Context.NOTIFICATION_SERVICE;

/**
 * Created by root on 08.12.17.
 */

public class NotificationBroadcastReceiver extends BroadcastReceiver {


    public static final int NOTIFICATION_ID = 1;

    @Override
    public void onReceive(Context context, Intent intent) {
        if (isNewPhotoIntent(intent)){

            NotificationCompat.Builder builder = new NotificationCompat.Builder(context);
            builder.setSmallIcon(R.drawable.ic_stat_notification);

            builder.setContentTitle("PhotoStream");



            Intent intentok = new Intent(context, MainActivity.class);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, intentok, 0);

            builder.setContentIntent(pendingIntent);


            builder.setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.ic_launcher));

            builder.setContentText(" Berühren um das neue Photo zu sehen");

            builder.setSubText("neues Photo verfügbar ");



            NotificationManager notificationManager = (NotificationManager) context.getSystemService(NOTIFICATION_SERVICE);


            notificationManager.notify(NOTIFICATION_ID, builder.build());







            // Das empfangene Photo aus dem Intent referenzieren (in diesem Beispiel ein Fake Photo)
            Photo receivedPhoto = intent.getParcelableExtra(IPhotoStreamClient.INTENT_KEY_PHOTO);
            String message = "ID des Photos: %s\nBeschreibung: %s\nPfad zur Bilddatei: %s";
            message = String.format(message, receivedPhoto.getId(), receivedPhoto.getDescription(), receivedPhoto.getImageFilePath());
            Toast.makeText(context, message, Toast.LENGTH_LONG).show();
        }

    }

    private boolean isNewPhotoIntent(Intent intent) {
        return intent.getAction().equals(IPhotoStreamClient.INTENT_ACTION_NEW_PHOTO_AVAILABLE);
    }
}
