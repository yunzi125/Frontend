package org.androidtown.jeoyo.activity;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Toast;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import org.androidtown.jeoyo.R;
import org.androidtown.jeoyo.fragment.ChatFragment;
import org.androidtown.jeoyo.fragment.HomeFragment;
import org.androidtown.jeoyo.fragment.MyPageFragment;

public class MainActivity extends AppCompatActivity
{
    BottomNavigationView bottomNavigationView;//바텀 네비게이션 뷰
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bottomNavigationView = findViewById(R.id.bottomNavi);

        //처음화면
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_frame, new HomeFragment()).commit(); //FrameLayout에 fragment.xml 띄우기

        // 바텀 네비게이션뷰 안의 아이템 설정
        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                switch (menuItem.getItemId())
                {
                    //item을 클릭시 id값을 가져와 FrameLayout에 fragment.xml띄우기
                    case R.id.tabChat:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new ChatFragment()).commit();
                        break;
                    case R.id.tabMain:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new HomeFragment()).commit();
                        break;
                    case R.id.tabMypage:
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_frame, new MyPageFragment()).commit();
                        break; }
                        return true;
            }
        });

    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        Toast.makeText(getApplicationContext(), "로그아웃", Toast.LENGTH_SHORT).show();   //토스트 메시지
        Intent intent = new Intent(getApplicationContext(), LoginActivity.class); //지금 액티비티에서 다른 액티비티로 이동하는 인텐트 설정
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);    //인텐트 플래그 설정
        startActivity(intent);  //인텐트 이동
        finish();   //현재 액티비티 종료
    }
}


