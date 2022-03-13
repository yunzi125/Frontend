package com.cookandroid.mycamera

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import androidx.core.view.GravityCompat
import com.yanzhenjie.permission.AndPermission
import com.yanzhenjie.permission.runtime.Permission
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        setSupportActionBar(toolbar)

        navigationView.setNavigationItemSelectedListener {
            when(it.itemId){
                R.id.item1->{
                    with(supportFragmentManager.beginTransaction()){
                        val fragment1 = FragmentA()
                        replace(R.id.container, fragment1)
                        commit()
                    }
                }
                R.id.item2->{
                    with(supportFragmentManager.beginTransaction()){
                        val fragment2 = FragmentB()
                        replace(R.id.container, fragment2)
                        commit()
                    }
                }
                R.id.item3->{
                    with(supportFragmentManager.beginTransaction()){
                        val fragment3 = FragmentC()
                        replace(R.id.container, fragment3)
                        commit()
                    }
                }
            }
            drawerLayout.closeDrawer(GravityCompat.START)
            return@setNavigationItemSelectedListener true
        }
        AndPermission.with(this)
            .runtime()
            .permission(Permission.Group.STORAGE)
            .onGranted{ permissions->
                Log.d("Main", "허용된 권한 갯수 : ${permissions.size}")
            }
            .onDenied{ permissions->
                Log.d("Main", "거부된 권한 갯수 : ${permissions.size}")
            }
            .start()
    }
    override fun onBackPressed(){
        if(drawerLayout.isDrawerOpen(GravityCompat.START)){
            drawerLayout.closeDrawer(GravityCompat.START)
        } else{
            super.onBackPressed()
        }
        super.onBackPressed()
    }
}