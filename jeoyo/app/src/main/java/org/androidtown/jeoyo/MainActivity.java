package org.androidtown.jeoyo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MenuItem;

import com.google.android.material.bottomnavigation.BottomNavigationView;

public class MainActivity extends AppCompatActivity
{
    BottomNavigationView bottomNavigationView;//바텀 네비게이션 뷰
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bottomNavigationView = findViewById(R.id.bottomNavi);

        //처음화면
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_frame, new fragment_home()).commit(); //FrameLayout에 fragment.xml 띄우기

        // 바텀 네비게이션뷰 안의 아이템 설정
        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                switch (menuItem.getItemId())
                {
                    //item을 클릭시 id값을 가져와 FrameLayout에 fragment.xml띄우기
                    case R.id.tabChat:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new fragment_chat()).commit();
                        break;
                    case R.id.tabMain:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new fragment_home()).commit();
                        break;
                    case R.id.tabMypage:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new fragment_mypage()).commit();
                        break; }
                        return true;
            }
        });
    } }


