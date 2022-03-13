package com.cookandroid.simplecalc

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast

class MainActivity : AppCompatActivity() {

    //1. 위젯 변수를 선언
    lateinit var edit1: EditText
    lateinit var edit2: EditText
    lateinit var btnAdd: Button;
    lateinit var btnSub: Button
    lateinit var btnMul: Button;
    lateinit var btnDiv: Button
    lateinit var textResult: TextView
    lateinit var num1: String;
    lateinit var num2: String
    var result: Int? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //2. 위젯 변수와 위젯 id를 연결
        edit1 = findViewById(R.id.EditNum1)
        edit2 = findViewById(R.id.EditNum2)
        btnAdd = findViewById(R.id.BtnAdd)
        btnSub = findViewById(R.id.BtnSub)
        btnMul = findViewById(R.id.BtnMul)
        btnDiv = findViewById(R.id.BtnDiv)
        textResult = findViewById(R.id.tvResult)

        //3. 동작을 정의
        btnAdd.setOnTouchListener { view, motionEvent ->
            // 3-1 EditText의 값을 읽어 온다
            num1 = edit1.text.toString() //edit1.getText().toString()
            num2 = edit2.text.toString()
            //num1이나 num2가 비어있다면
            if (num1.trim() == "" || num2.trim() == "") {
                Toast.makeText(applicationContext, "입력 값이 비었습니다", Toast.LENGTH_SHORT).show()
            } else {
                // 3-2 계산
                result = Integer.parseInt(num1) + Integer.parseInt(num2)
                // 3-3 계산된 결과를 TextView 보여준다
                textResult.text = "계산 결과 : " + result.toString() //textResult.setText("계산 결과 : " + result.toString()
                //return
            }
            false
        }
        btnSub.setOnTouchListener { view, motionEvent ->
            // 3-1 EditText의 값을 읽어 온다
            num1 = edit1.text.toString() //edit1.getText().toString()
            num2 = edit2.text.toString()
            //num1이나 num2가 비어있다면
            if (num1.trim() == "" || num2.trim() == "") {
                Toast.makeText(applicationContext, "입력 값이 비었습니다", Toast.LENGTH_SHORT).show()
            } else {
                // 3-2 계산
                result = Integer.parseInt(num1) - Integer.parseInt(num2)
                // 3-3 계산된 결과를 TextView 보여준다
                textResult.text = "계산 결과 : " + result.toString() //textResult.setText("계산 결과 : " + result.toString()
                //return
            }
        false
        }


        btnMul.setOnTouchListener { view, motionEvent ->
            // 3-1 EditText의 값을 읽어 온다
            num1 = edit1.text.toString() //edit1.getText().toString()
            num2 = edit2.text.toString()
            //num1이나 num2가 비어있다면
            if(num1.trim() == "" || num2.trim() == "") {
                Toast.makeText(applicationContext, "입력 값이 비었습니다", Toast.LENGTH_SHORT).show()
            }else {
                // 3-2 계산
                result = Integer.parseInt(num1) * Integer.parseInt(num2)
                // 3-3 계산된 결과를 TextView 보여준다
                textResult.text = "계산 결과 : " + result.toString() //textResult.setText("계산 결과 : " + result.toString()
                //return
            }
            false
        }

        btnDiv.setOnTouchListener { view, motionEvent ->
            // 3-1 EditText의 값을 읽어 온다
            num1 = edit1.text.toString() //edit1.getText().toString()
            num2 = edit2.text.toString()
            //num1이나 num2가 비어있다면
            if(num1.trim() == "" || num2.trim() == "") {
                Toast.makeText(applicationContext, "입력 값이 비었습니다", Toast.LENGTH_SHORT).show()
            }else {
                if(num2.trim() == "0"){
                    Toast.makeText(applicationContext,
                    "0으로 나머지 값 안됩니다!", Toast.LENGTH_SHORT).show()
                } else{
                    // 3-2 계산
                    result = Integer.parseInt(num1) / Integer.parseInt(num2)
                    // 3-3 계산된 결과를 TextView 보여준다
                    textResult.text =
                            "계산 결과 : " + result.toString() //textResult.setText("계산 결과 : " + result.toString()
                    //return
                }
            }


            false
        }
}}