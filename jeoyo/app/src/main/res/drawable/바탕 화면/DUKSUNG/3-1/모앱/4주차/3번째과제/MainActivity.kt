package com.cookandroid.tablecalc

// 20190969 박고은
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast

class MainActivity : AppCompatActivity() {

    //1. 위젯 변수를 선언
    lateinit internal var edit1: EditText
    lateinit internal var edit2: EditText
    lateinit internal var btnAdd: Button;
    lateinit internal var btnSub: Button
    lateinit internal var btnMul: Button;
    lateinit internal var btnDiv: Button
    lateinit internal var textResult: TextView
    lateinit internal var num1: String;
    lateinit internal var num2: String
    internal var result: Int? = null

    //10개 숫자 버튼 배열
    internal var numButtons = ArrayList<Button>(10)
    //10개 숫자 버튼의 id 값 배열
    internal var numBtnIDs= arrayOf(R.id.btnNum0, R.id.btnNum1, R.id.btnNum2, R.id.btnNum3, R.id.btnNum4, R.id.btnNum5,
    R.id.btnNum6, R.id.btnNum7, R.id.btnNum8, R.id.btnNum9)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //2. 위젯 변수와 위젯 id를 연결
        edit1 = findViewById(R.id.Edit1)
        edit2 = findViewById(R.id.Edit2)
        btnAdd = findViewById(R.id.BtnAdd)
        btnSub = findViewById(R.id.BtnSub)
        btnMul = findViewById(R.id.BtnMul)
        btnDiv = findViewById(R.id.BtnDiv)
        textResult = findViewById(R.id.TextResult)

        //numButtons[0]=findViewById(R.id.btnNum0)
        //numButtons[0]=findViewById(numBtnIDs[0])
        for(i in 0..9 step 1){
            numButtons.add(findViewById(numBtnIDs[i]))
        }


        //3. 동작을 정의
        for(i in 0..numButtons.size-1){ // for(i in 0..9)
            numButtons[i].setOnClickListener {
                if(edit1.isFocused == true){
                    num1 = edit1.text.toString() + numButtons[i].getText().toString()
                    // num1=edit1.text.toString() + numButtons[i].text.toString()
                    edit1.setText(num1)
                }
                else if(edit2.isFocused == true){
                    num2 = edit2.text.toString() + numButtons[i].getText().toString()
                    edit2.setText(num2)
                }
                else {
                    Toast.makeText(applicationContext, "먼저 에디트텍스트를 선택하세요",
                    Toast.LENGTH_SHORT).show()
                }
            }
        }


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
    }
}