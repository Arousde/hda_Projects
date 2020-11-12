package heinemann.photostreams;

import android.os.Bundle;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

import hochschuledarmstadt.photostream_tools.IPhotoStreamClient;
import hochschuledarmstadt.photostream_tools.PhotoStreamActivity;
import hochschuledarmstadt.photostream_tools.adapter.BaseCommentAdapter;
import hochschuledarmstadt.photostream_tools.adapter.DividerItemDecoration;
import hochschuledarmstadt.photostream_tools.callback.OnCommentUploadFailedListener;
import hochschuledarmstadt.photostream_tools.callback.OnCommentsReceivedListener;
import hochschuledarmstadt.photostream_tools.callback.OnNewCommentReceivedListener;
import hochschuledarmstadt.photostream_tools.callback.OnRequestListener;
import hochschuledarmstadt.photostream_tools.model.Comment;
import hochschuledarmstadt.photostream_tools.model.HttpError;

import static heinemann.photostreams.MainActivity.PHOTO_ID;

/**
 * Created by root on 09.12.17.
 */

public class CommentActivity extends PhotoStreamActivity implements OnRequestListener,
        OnCommentsReceivedListener, OnNewCommentReceivedListener, OnCommentUploadFailedListener,View.OnClickListener {





    // Key für das Speichern der Kommentare in der Methode {@link CommentActivity#onSaveInstanceState(Bundle)}"
    private static final String KEY_ADAPTER = "KEY_ADAPTER";

    // Es werden beispielhaft die Kommentare zu dem Photo mit dieser ID abgerufen


    // Widget für das Anzeigen der Kommentare in einer Liste
    private RecyclerView recyclerView;

    // Container, der die Kommentare enthält
    private CommentAdapter adapter;

    // Input für neuen Kommentar
    private EditText editText;

    // Methode wird von der Bibliothek automatisch aufgerufen, wenn die Activity an den Service gebunden wurde.
    @Override
    protected void onPhotoStreamServiceConnected(IPhotoStreamClient photoStreamClient, Bundle savedInstanceState) {
        photoStreamClient.addOnCommentsReceivedListener(this);
        photoStreamClient.addOnNewCommentReceivedListener(this);
        /*
            Kommentare laden, wenn die Activity zum ersten Mal gestartet wird
         */
        if (savedInstanceState == null)
            photoStreamClient.loadComments(PHOTO_ID);
    }

    // Methode wird von der Bibliothek automatisch aufgerufen, wenn der Service von der Activity entbunden wurde.
    @Override
    protected void onPhotoStreamServiceDisconnected(IPhotoStreamClient photoStreamClient) {
        // Listener wieder entfernen um Memory Leak zu vermeiden
        photoStreamClient.removeOnCommentsReceivedListener(this);
        photoStreamClient.removeOnNewCommentReceivedListener(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_comment);

        // EditText referenzieren
        editText = (EditText) findViewById(R.id.editText);

        // Callback festlegen, wenn auf den Action Button der Tastatur gedrückt wurde
        editText.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionId, KeyEvent keyEvent) {
                // Vergleich ob entsprechende Bits in der actionId gesetzt sind
                if ((actionId & EditorInfo.IME_MASK_ACTION) == EditorInfo.IME_ACTION_DONE) {
                    String comment = editText.getText().toString().trim();
                    // Kommentar nur senden, wenn Eingabe nicht leer ist
                    if (!comment.isEmpty()) {
                        editText.setEnabled(false);
                        getPhotoStreamClient().uploadComment(PHOTO_ID, comment);
                    } else {
                        Toast.makeText(CommentActivity.this,"no_comment_input", Toast.LENGTH_SHORT).show();
                    }
                    // Zurückgegeben, dass das Event verarbeitet wurde
                    return true;
                }
                return false;
            }
        });

        // Beim ersten Start der Activity den Fokus auf das Eingabefeld setzen
        if (savedInstanceState == null)
            editText.requestFocus();

        // RecyclerView referenzieren
        recyclerView = (RecyclerView) findViewById(R.id.recyclerView);
        // LinearLayoutManager setzen (Elemente in der angezeigten Liste werden vertikal sequentiell dargestellt)
        recyclerView.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false));
        // Visuellen Begrenzer setzen für Kommentare in der Liste
        recyclerView.addItemDecoration(new DividerItemDecoration(this));
        // Standard Animationen setzen
        recyclerView.setItemAnimator(new DefaultItemAnimator());
        adapter = new CommentAdapter(this);

        // Registriert einen OnItemClickListener für die View mit der id "textView"
        // innerhalb eines Elements in der Recyclerview (siehe layout "comment_item.xml")
        adapter.setOnItemClickListener(R.id.textView, new BaseCommentAdapter.OnItemClickListener<CommentAdapter.CommentViewHolder>() {
            @Override
            public void onItemClicked(CommentAdapter.CommentViewHolder viewHolder, View v, Comment comment) {
                String message = String.format("Comment Id: %d", comment.getId());
                Toast.makeText(CommentActivity.this, message, Toast.LENGTH_SHORT).show();
            }
        });

        // Wenn die Activity neu aufgebaut wird
        if (savedInstanceState != null) {
            // dann die Kommentare aus der vorherigen Activity Instanz wiederherstellen/referenzieren
            Bundle bundle = savedInstanceState.getBundle(KEY_ADAPTER);
            // und an den Adapter übergeben
            adapter.restoreInstanceState(bundle);
        }

        // Der RecyclerView abschließend den Adapter als Datenquelle zuweisen
        recyclerView.setAdapter(adapter);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        // Kommentare aus dem Adapter im Bundle speichern
        outState.putBundle(KEY_ADAPTER, adapter.saveInstanceState());
    }

    @Override
    public void onCommentsReceived(int photoId, List<Comment> comments) {
        // Wenn die Kommentare zur aktuellen PHOTO_ID gehören
        if (PHOTO_ID == photoId)
            // dann die Kommentare setzen
            adapter.set(comments);
    }

    @Override
    public void onReceiveCommentsFailed(int photoId, HttpError httpError) {
        String title = String.format("Could not load comments for photo with id %d", photoId);
        Utils.showErrorInAlertDialog(this, title, httpError);
    }

    @Override
    public void onRequestStarted() {
        // ProgressBar anzeigen
        //findViewById(R.id.progressCircle).setVisibility(ProgressBar.VISIBLE);
    }

    @Override
    public void onRequestFinished() {
        // ProgressBar verstecken
      //  findViewById(R.id.progressCircle).setVisibility(ProgressBar.GONE);
    }

    @Override
    public void onNewCommentReceived(Comment comment) {
        // Wenn der Kommentare zur aktuellen PHOTO_ID gehört
        if (comment.getPhotoId() == PHOTO_ID) {
            // Dann den Kommentar ans Ende der Liste hinzufügen
            adapter.add(comment);
            // Eingabe wieder freigeben
            editText.setEnabled(true);
            // Wenn der Kommentar von diesem Gerät stammt
            if (comment.isDeleteable()) {
                // dann die Eingabe leeren
                editText.setText("");
                // und ans Ende der Liste springen
                recyclerView.scrollToPosition(adapter.getItemCount() - 1);
            }
        }
    }

    @Override
    public void onCommentUploadFailed(HttpError httpError) {
        // Fehler anzeigen in einem AlertDialog
        Utils.showErrorInAlertDialog(this, "Fehler beim Senden eines Kommentars", httpError);
        // Eingabe für den Nutzer wieder freigeben
        editText.setEnabled(true);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case  R.id.comdel :
            {
Comment co = (Comment) v.getTag();
getPhotoStreamClient().deleteComment(co.getId());
if(co.isDeleteable()){
    adapter.remove(co.getId());
}else
{
    Toast.makeText(this, " Not authorised ", Toast.LENGTH_SHORT).show();
}
            }break;
        }
    }
}
