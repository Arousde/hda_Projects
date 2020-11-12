package heinemann.photostreams;

/**
 * Created by aross on 10.11.2017.
 */
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import hochschuledarmstadt.photostream_tools.adapter.BasePhotoAdapter;
//import de.hda.photostreamexamples.R;
import hochschuledarmstadt.photostream_tools.model.BaseItem;
import hochschuledarmstadt.photostream_tools.model.Photo;

public class PhotoAdapter extends BasePhotoAdapter<PhotoAdapter.PhotoViewHolder>{

private View.OnClickListener mListner;

    // Konstanten für die Animation des angezeigten Bilds
    private static final float BEGIN_SCALE = 0.5f, BEGIN_ALPHA = 0.1f, MAX = 1.0f;
    private static final int DURATION_IN_MILLIS = 500;

    public PhotoAdapter(View.OnClickListener listener){
        super();
        mListner = listener;


    }

    public PhotoAdapter(int cacheSizeInMegaByte) {
        super(cacheSizeInMegaByte);
    }

    @Override
    public PhotoViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        // Objekt referenzieren für das Erzeugen des Layouts für ein Element in der angezeigten Liste
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        // Ein neues Layout für ein Element erzeugen
        View itemView = layoutInflater.inflate(R.layout.photo_item, parent, false);
        // ViewHolder erzeugen und dabei das erzeugte Layout übergeben
        return new PhotoViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(final PhotoViewHolder holder, int position) {
        super.onBindViewHolder(holder, position);
        // Photo an der angegebenen Position referenzieren
        final Photo photo = getItemAtPosition(position);
        // Bitmap anhand des Photo Objekts laden und in der ImageView setzen
        loadBitmapIntoImageViewAsync(holder, holder.imageView, photo);
        holder.comment.setOnClickListener(mListner);
        holder.favorite.setOnClickListener(mListner);
        holder.del.setOnClickListener(mListner);
       if(photo.isFavorite()){
           holder.favorite.setImageResource(R.drawable.favv);

       }else{
           holder.favorite.setImageResource(R.drawable.favadd);

       }
        holder.favorite.setTag(photo);
        holder.comment.setTag(photo);
        holder.del.setTag(photo);
    }

    @Override
    protected void onBitmapLoadedIntoImageView(ImageView imageView) {
       //Bitmap ist hiermit in der ImageView gesetzt.
        // Jetzt kann man zum Beispiel noch eine Animation durchführen
       imageView.setScaleX(BEGIN_SCALE);
        imageView.setScaleY(BEGIN_SCALE);
        imageView.setAlpha(BEGIN_ALPHA);
        imageView.animate().scaleX(MAX).scaleY(MAX).alpha(MAX).setDuration(DURATION_IN_MILLIS).start();
    }




    public static class PhotoViewHolder extends RecyclerView.ViewHolder {

        public final ImageView imageView;
        public  ImageButton favorite ;
        public  ImageButton comment ;
        public ImageButton del;

        // itemView entspricht dem erzeugten Layout aus der onCreateViewHolder() Methode
        public PhotoViewHolder(View itemView) {
            super(itemView);
            // Views referenzieren, auf die man in der onBindViewHolder
            // Methode zugreifen möchte
            imageView =  itemView.findViewById(R.id.imageView);
            favorite = itemView.findViewById(R.id.favourite);
            comment = itemView.findViewById(R.id.mycomment);
            comment.setImageResource(R.drawable.comment);
            del = itemView.findViewById(R.id.deleteimg);
            del.setImageResource(R.drawable.tr);
    }
    }



    @Override
    public void remove(int id) {
        super.remove(id);
    }


}

