package com.cookandroid.mynavermovie

import android.text.Layout
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import kotlinx.android.synthetic.main.movieitem.view.*

class MovieItemAdapter (var items:ArrayList<MovieItem>) : RecyclerView.Adapter<MovieItemAdapter.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MovieItemAdapter.ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.movieitem, parent, false)
        return ViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: MovieItemAdapter.ViewHolder, position: Int) {
        val item = items[position]
        holder.setItem(item)
    }

    override fun getItemCount(): Int = items.count()

    inner class ViewHolder(itemView : View) : RecyclerView.ViewHolder(itemView){
        fun setItem(item:MovieItem) {
            itemView.name.text = item.title
            itemView.score1.text = item.score1
            itemView.score2.text = item.score2
            itemView.reserve.text = "예매율 : " + item.reserve + "%"
            Glide.with(itemView).load(item.imgsrc).into(itemView.poster)
        }
    }
}