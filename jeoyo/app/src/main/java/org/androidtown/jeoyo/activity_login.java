package org.androidtown.jeoyo;

import android.content.Intent;
import android.os.Bundle;

import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;

import android.view.View;
import android.widget.Button;

import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import org.androidtown.jeoyo.databinding.ActivityLoginBinding;

public class activity_login extends AppCompatActivity {

    private AppBarConfiguration appBarConfiguration;
    private ActivityLoginBinding binding;


    public activity_login() {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Intent intent = getIntent();

        Button login = (Button)findViewById(R.id.button_login);
        login.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);	//intent 에 명시된 액티비티로 이동
                finish();	//현재 액티비티 종료
            }
        });

    }

}