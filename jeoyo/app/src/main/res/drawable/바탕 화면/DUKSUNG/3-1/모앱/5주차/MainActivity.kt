package com.cookandroid.myviewpager

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.fragment.app.FragmentActivity
import androidx.viewpager2.widget.ViewPager2
import kotlinx.android.synthetic.main.activity_main.*

// 1변수선언 2id연결 3동작
class MainActivity : FragmentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        pager.adapter = VpagerAdapter(this)
        pager.orientation = ViewPager2.ORIENTATION_HORIZONTAL
        pager.offscreenPageLimit = 3


        indicator.setViewPager(pager)
        indicator.createIndicators(3, 0)

        pager.registerOnPageChangeCallback(object: ViewPager2.OnPageChangeCallback() {
            override fun onPageSelected(position: Int) {
                super.onPageSelected(position)
                indicator.animatePageSelected(position)
                Toast.makeText(application, "${position+1} 페이지 선택됨", Toast.LENGTH_LONG).show()
            }
        })
        button.setOnClickListener {
            pager.currentItem = 0
        }
        button2.setOnClickListener {
            pager.currentItem = 1
        }
        button3.setOnClickListener {
            pager.currentItem = 2
        }
    }
}