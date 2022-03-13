package org.techtown.myopenhospital

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.hospital.view.*

class HospitalAdapter(var items : ArrayList<Hospital>) :RecyclerView.Adapter<HospitalAdapter.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): HospitalAdapter.ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.hospital, parent, false)
        return ViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: HospitalAdapter.ViewHolder, position: Int) {
        val item = items[position]
        holder.setItem(item)
    }

    override fun getItemCount() = items.count()

    inner class ViewHolder(itemView : View) : RecyclerView.ViewHolder(itemView){
        fun setItem(item:Hospital){
            itemView.listview_text1.text = item.yadmNm
            itemView.listview_text2.text = item.sidoNm
            itemView.listview_text3.text = item.phone_number
        }
    }
}