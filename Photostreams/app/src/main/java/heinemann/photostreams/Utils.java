package heinemann.photostreams;

/**
 * Created by aross on 10.11.2017.
 */
import android.content.Context;
import android.support.v7.app.AlertDialog;

import hochschuledarmstadt.photostream_tools.model.HttpError;
import hochschuledarmstadt.photostream_tools.model.Photo;

public class Utils {

    public static void showErrorInAlertDialog(Context context, String title, HttpError httpError){
        int responseCode = httpError.getResponseCode();
        String message = String.format("Response Code: %s\nMessage:%s", responseCode, httpError.getMessage());
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(title);
        builder.setMessage(message);
        builder.create().show();
    }
}
