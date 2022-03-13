package com.cookandroid.myfirebase

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import androidx.recyclerview.widget.LinearLayoutManager
import com.google.firebase.database.*
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import kotlin.collections.HashMap

class MainActivity : AppCompatActivity() {
    private lateinit var adapter:MovieCommentAdapter
    private lateinit var databaseRef: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //recyclerView.LayoutManager = LinearLayoutManagaer(this)
        val layoutManager = LinearLayoutManager(this)
        layoutManager.setReverseLayout(true)
        layoutManager.setStackFromEnd(true)
        recyclerView.layoutManager = layoutManager

        adapter = MovieCommentAdapter()
       // adapter.items.add(MovieComment("0", "sky2****", "1분전", 5, "정말 스릴넘치는 영화였어요. 한 번 더 보고싶은 영화!!!", 5))
        //adapter.items.add(MovieComment("1", "john****", "3분전", 4, "재미있어요.", 5))
        //adapter.items.add(MovieComment("2", "acou****", "12분전", 4, "실화라고 생각하기에는 너무 영화같은...", 5))
        recyclerView.adapter = adapter

        databaseRef = FirebaseDatabase.getInstance("https://mykotlinproject-a9d03-default-rtdb.firebaseio.com/").reference

        saveButton.setOnClickListener {
            val author = input1.text.toString()
            val rating = ratingBar.rating.toLong()
            val contents = input2.text.toString()
            val recommendCount = 0L

            saveComment(author, rating, contents, recommendCount)
        }
        databaseRef.orderByKey().limitToFirst(10).addValueEventListener(object: ValueEventListener {
            override fun onCancelled(error: DatabaseError) {
                Log.e("test", "loadItem:onCancelled : ${error.toException()}")
            }

            override fun onDataChange(snapshot: DataSnapshot) {
                loadCommentList(snapshot)
            }
        })
    }

    fun loadCommentList(dataSnapshot: DataSnapshot) {
        val collectionIterator = dataSnapshot!!.children.iterator()
        if (collectionIterator.hasNext()) {
            adapter.items.clear()
            val comments = collectionIterator.next()
            val itemsIterator = comments.children.iterator()
            while (itemsIterator.hasNext()) {
                val currentItem = itemsIterator.next()
                val map = currentItem.value as HashMap<String, Any>
                val objectId = map["objectId"].toString()
                val author = map["author"].toString()
                var commentTime = Date(map["timestamp"] as Long).toString()
                val rating = map["rating"] as Long
                val contents = map["contents"] as String
                val recommendCount = map["recommendCount"] as Long

                adapter.items.add(MovieComment(objectId, author, commentTime, rating, contents, recommendCount))
            }
            adapter.notifyDataSetChanged()
        }
    }
    fun saveComment(author:String, rating:Long, contents:String, recommendCount:Long){
        var key : String? = databaseRef.child("comments").push().getKey()
        val comment = MovieComment(key!!, author, "", rating, contents, recommendCount)
        val commentValues : HashMap<String, Any> = comment.toMap()
        commentValues["timestamp"] = ServerValue.TIMESTAMP
        val childUpdates: MutableMap<String, Any> = HashMap()
        childUpdates["/comment/$key"] = commentValues
        databaseRef.updateChildren(childUpdates)
    }
}