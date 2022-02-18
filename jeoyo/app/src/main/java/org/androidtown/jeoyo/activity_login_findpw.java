package org.androidtown.jeoyo;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.bottomnavigation.BottomNavigationView;


public class activity_login_findpw extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_findpw);

        ImageView back = findViewById(R.id.back);
        back.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), activity_login.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });

        Button button_login = findViewById(R.id.button_login);
        button_login.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Toast.makeText(getApplicationContext(), "재설정 링크가 포함된 메일이 발송되었어요.", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(getApplicationContext(), activity_login.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });

    } }


