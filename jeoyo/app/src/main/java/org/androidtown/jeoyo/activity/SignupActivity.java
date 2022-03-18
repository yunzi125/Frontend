package org.androidtown.jeoyo.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import org.androidtown.jeoyo.R;

public class SignupActivity extends Activity {

    Button button_next;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);

        Intent intent = getIntent();
        button_next = (Button) findViewById(R.id.button_next);


        button_next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                //Intent intent = new Intent(SignupActivity.this, signup_region_activity.class);
                startActivity(intent);
                finish();
            }
        });
    }
}