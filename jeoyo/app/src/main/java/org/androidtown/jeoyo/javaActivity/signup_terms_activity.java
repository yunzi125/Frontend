package org.androidtown.jeoyo.javaActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import org.androidtown.jeoyo.R;

//figma 0.1.1(이용약관)
public class signup_terms_activity extends Activity {
    RadioButton termrd01, termrd02, termrd03;
    RadioGroup radioGroup1;
    Button button_next;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup_terms);

        Intent intent = getIntent();

        radioGroup1 = (RadioGroup) findViewById(R.id.radioGroup1);
        termrd01 = (RadioButton) findViewById(R.id.termrd01);
        termrd02 = (RadioButton) findViewById(R.id.termrd02);
        termrd03 = (RadioButton) findViewById(R.id.termrd03);
        button_next = (Button) findViewById(R.id.button_next);


        button_next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), signup_email_activity.class);
                startActivity(intent);
                finish();
            }
        });
    }
}