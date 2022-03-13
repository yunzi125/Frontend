package com.cookandroid.myaddress

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        title = "나의 주소록"

        recyclerView.layoutManager = GridLayoutManager(this, 2)
        val adapter = PersonAdapter()
        adapter.items.add(Person("홍길동", "010-1234-5678"))
        adapter.items.add(Person("성춘향", "010-3333-5555"))
        adapter.items.add(Person("이덕성", "010-7777-9999"))

        recyclerView.adapter = adapter
    }
}