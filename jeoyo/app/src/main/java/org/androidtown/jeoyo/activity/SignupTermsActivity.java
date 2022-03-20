package org.androidtown.jeoyo.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;

import org.androidtown.jeoyo.R;

//figma 0.1.1(이용약관)
public class SignupTermsActivity extends Activity {
    RadioButton termrd01, termrd02, termrd03;
    Button button_next;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup_terms);

        Intent intent = getIntent();

        termrd01 = (RadioButton) findViewById(R.id.termrd01);
        termrd02 = (RadioButton) findViewById(R.id.termrd02);
        termrd03 = (RadioButton) findViewById(R.id.termrd03);
        button_next = (Button) findViewById(R.id.button_next);
        button_next.setEnabled(false);

        button_next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(SignupTermsActivity.this, SignupEmailActivity.class);
                startActivity(intent);
                finish();
            }
        });
    }

    public void onRadioButtonClicked(View v){
        boolean checked=((RadioButton)v).isChecked();

        if((termrd01.isChecked()==true)&&(termrd02.isChecked()==true)){
            button_next.setEnabled(true);
        }
    }
}