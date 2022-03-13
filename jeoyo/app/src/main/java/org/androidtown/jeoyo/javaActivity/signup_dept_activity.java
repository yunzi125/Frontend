package org.androidtown.jeoyo.javaActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import org.androidtown.jeoyo.R;

public class signup_dept_activity extends Activity {

    Button button_next;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup_dept);

        Intent intent = getIntent();
        button_next = (Button) findViewById(R.id.button_next);

        button_next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Intent intent = new Intent(getApplicationContext(), signup_activity.class);
                startActivity(intent);
                finish();
            }
        });
    }
}