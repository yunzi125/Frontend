package org.androidtown.jeoyo.javaActivity;

import android.content.Intent;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.navigation.ui.AppBarConfiguration;

import org.androidtown.jeoyo.R;
import org.androidtown.jeoyo.databinding.ActivityLoginBinding;

public class login_activity extends AppCompatActivity {

    private AppBarConfiguration appBarConfiguration;
    private ActivityLoginBinding binding;

    public login_activity() {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Intent intent = getIntent();

        Button login = (Button)findViewById(R.id.button_login);
        TextView findPwText = findViewById(R.id.findPwText);
        TextView signUpText = findViewById(R.id.signUpText);

        login.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });

        findPwText.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), login_findpw_activity.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });

        signUpText.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), signup_terms_activity.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });



    }

}