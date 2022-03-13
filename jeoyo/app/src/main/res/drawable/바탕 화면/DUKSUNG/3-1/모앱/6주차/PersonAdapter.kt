package com.cookandroid.myaddress

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.person.view.*

class PersonAdapter : RecyclerView.Adapter<PersonAdapter.ViewHolder>() {
    var items = ArrayList<Person>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.person, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = items.size

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = items[position]
        holder.setItem(item)
    }

    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
       init{
           itemView.setOnClickListener{
               Toast.makeText(itemView?.context,
               "클릭 = ${itemView.textView.text}",
                   Toast.LENGTH_LONG).show()
           }
       }
        fun setItem(item:Person){
            itemView.textView.text = item.name
            itemView.textView2.text = item.mobile
        }
    }
}