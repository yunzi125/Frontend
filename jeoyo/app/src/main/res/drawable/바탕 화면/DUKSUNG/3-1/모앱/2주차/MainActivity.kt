package com.cookandroid.a3buttontest

import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {
    lateinit var btn_daum:Button
    lateinit var btn_119:Button
    lateinit var btn_gallery:Button
    lateinit var btn_exit:Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        btn_daum=findViewById<Button>(R.id.btn_daum)
        btn_119=findViewById<Button>(R.id.btn_119)
        btn_gallery=findViewById<Button>(R.id.btn_gallery)
        btn_exit=findViewById<Button>(R.id.btn_exit)

        btn_daum.setOnClickListener {
            val mIntent = Intent(Intent.ACTION_VIEW, Uri.parse("http://m.daum.net"))

            startActivity(mIntent)
        }
        btn_119.setOnClickListener {
            val mIntent = Intent(Intent.ACTION_VIEW, Uri.parse("tel:/119"))

            startActivity(mIntent)
        }
        btn_gallery.setOnClickListener {
            val mIntent=Intent(Intent.ACTION_VIEW,
            Uri.parse("content://media/internal/images/media"))
            startActivity(mIntent)
        }
        btn_exit.setOnClickListener { finish() }
    }
}