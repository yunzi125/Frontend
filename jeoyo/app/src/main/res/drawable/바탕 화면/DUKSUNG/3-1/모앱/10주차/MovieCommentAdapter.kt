package com.cookandroid.myfirebase

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.movie_comment.view.*

class MovieCommentAdapter : RecyclerView.Adapter<MovieCommentAdapter.ViewHolder>(){
    var items = ArrayList<MovieComment>()
    
    override fun onCreateViewHolder(
        parent: ViewGroup,
        viewType: Int
    ): MovieCommentAdapter.ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.movie_comment, parent, false)
        return ViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: MovieCommentAdapter.ViewHolder, position: Int) {
        val item = items[position]
        holder.setItem(item)
    }

    override fun getItemCount() = items.size


    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
        fun setItem(item:MovieComment){
            itemView.idTextView.text=item.author
            itemView.idTextView2.text=item.date
            itemView.ratingBar.rating = item.rating.toFloat()
            itemView.contentsTextView.text=item.contents
            itemView.recommendCountTextView.text=item.recommendCount.toString()
        }
    }
}

