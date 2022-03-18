package org.androidtown.jeoyo.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.androidtown.jeoyo.R;

public class SignupEmailActivity extends Activity {

    Button button_next;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup_email);

        Intent intent = getIntent();

        TextView textView2 = findViewById(R.id.textView2);
        button_next = (Button) findViewById(R.id.button_next);

        textView2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                String str=textView2.getText().toString();
                if(textView2.length()==0){
                    Toast.makeText(getApplicationContext(), "이메일을 다시 한 번 확인해주세요!", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(getApplicationContext(), "인증 번호가 포함된 메일이 발송되었어요.", Toast.LENGTH_SHORT).show();
                }
                Intent intent = new Intent(getApplicationContext(), SignupEmailActivity.class);
                startActivity(intent);
                finish();
            }
        });

        button_next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), SignupDeptActivity.class);
                startActivity(intent);
                finish();
            }
        });
    }
}
