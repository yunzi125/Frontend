package com.cookandroid.mymenu

import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.ContextMenu
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.Button
import android.widget.LinearLayout
import android.widget.TextView
import android.widget.Toast
import com.google.android.material.snackbar.Snackbar

class MainActivity : AppCompatActivity() {
    lateinit var baseLayout : LinearLayout
    lateinit var button1 : Button
    lateinit var button2 : Button
    lateinit var button3 : Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        title = "메뉴 테스트"

        baseLayout = findViewById(R.id.baseLayout)
        button1 = findViewById(R.id.button1)

        button2 = findViewById(R.id.button2)
        registerForContextMenu(button2)
        button3 = findViewById(R.id.button3)
        registerForContextMenu(button3)
    }
    override fun onCreateContextMenu(
        menu: ContextMenu?,
        v: View?,
        menuInfo: ContextMenu.ContextMenuInfo?
    ) {
        super.onCreateContextMenu(menu, v, menuInfo)
        var mInflater = menuInflater
        if(v == button2){
            menu!!.setHeaderTitle("배경색 변경")
            mInflater.inflate(R.menu.menu2, menu)
        }
        if(v == button3) {mInflater.inflate(R.menu.menu3, menu)}
    }

    override fun onContextItemSelected(item: MenuItem): Boolean {
        super.onContextItemSelected(item)
        when(item.itemId){
            R.id.itemRed -> {
                baseLayout.setBackgroundColor(Color.RED)
                return true}
            R.id.itemGreen -> {
                baseLayout.setBackgroundColor(Color.GREEN)
                return true}
            R.id.itemBlue -> {
                baseLayout.setBackgroundColor(Color.BLUE)
                return true }
            R.id.subRotate -> {
                button3.rotation = 45f
                return true }
            R.id.subSize -> {
                button3.scaleX = 2f
                return true }
        }
        return false
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)
        var mInflater = menuInflater
        mInflater.inflate(R.menu.menu1, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when(item.itemId){
            R.id.itemRed -> {
                baseLayout.setBackgroundColor(Color.RED)
                Toast.makeText(this, "배경색 빨간색으로 변경", Toast.LENGTH_LONG).show()
                return true}
            R.id.itemGreen -> {
                baseLayout.setBackgroundColor(Color.GREEN)
                showToast("배경색 초록색으로 변경")
                return true}
            R.id.itemBlue -> {
                baseLayout.setBackgroundColor(Color.BLUE)
                Snackbar.make(baseLayout, "배경색 파란색으로 변경", Snackbar.LENGTH_INDEFINITE).show()
                return true }
            R.id.subRotate -> {
                button1.rotation = 45f
                Snackbar.make(baseLayout, "버튼 회전으로 변경", Snackbar.LENGTH_INDEFINITE)
                    .setAction("취소", {baseLayout.setBackgroundColor(Color.YELLOW)})
                    .show()
                return true }
            R.id.subSize -> {
                button1.scaleX = 2f
                showSnackbar("버튼 크기 변경")
                return true }
        }
        return false
    }

    fun showToast(msg : String){
        var toast = Toast(this@MainActivity)

        var toastView = View.inflate(this@MainActivity, R.layout.toast1, null)
        var toastTV = toastView.findViewById<TextView>(R.id.toastT1)
        toastTV.setText(msg)

        toast.view = toastView
        toast.show()
    }

    fun showSnackbar(msg : String){
        var sb = Snackbar.make(baseLayout, "", Snackbar.LENGTH_INDEFINITE)
        var layout = sb.view as Snackbar.SnackbarLayout

        var toastView = View.inflate(this@MainActivity, R.layout.toast1, null)
        var toastTV = toastView.findViewById<TextView>(R.id.toastT1)
        toastTV.setText(msg)

        layout.addView(toastView)
        sb.show()
    }
}