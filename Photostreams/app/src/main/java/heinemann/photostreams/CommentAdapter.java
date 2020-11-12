package heinemann.photostreams;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.TextView;

import hochschuledarmstadt.photostream_tools.adapter.BaseCommentAdapter;
import hochschuledarmstadt.photostream_tools.model.Comment;

/**
 * Created by root on 09.12.17.
 */

public class CommentAdapter extends BaseCommentAdapter<CommentAdapter.CommentViewHolder> {

private View.OnClickListener mlListener;

    public CommentAdapter(View.OnClickListener listener) {
        super();
        mlListener= listener;
    }

    public static class CommentViewHolder extends RecyclerView.ViewHolder {
        public TextView textView;
        public ImageButton del_cmt;
        public CommentViewHolder(View itemView) {
            super(itemView);
            textView = (TextView) itemView.findViewById(R.id.textView);
            del_cmt= (ImageButton) itemView.findViewById(R.id.comdel);
        }
    }



    @Override
    public CommentViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View v = inflater.inflate(R.layout.comment_item, parent, false);
        CommentViewHolder viewHolder = new CommentViewHolder(v);
        return viewHolder;
    }

    /*
        Wird intern von der RecyclerView aufgerufen, um den Inhalt einer View,
        mit Informationen aus dem Element an der "position", zu aktualisieren
     */
    @Override
    public void onBindViewHolder(CommentViewHolder holder, int position) {
        super.onBindViewHolder(holder, position);
        Comment comment = getItemAtPosition(position);
        holder.textView.setText(comment.getMessage());
        if(!comment.isDeleteable()){
            holder.del_cmt.setVisibility(View.GONE);
        }
        holder.del_cmt.setOnClickListener(mlListener);
        holder.del_cmt.setTag(comment);
    }

}
