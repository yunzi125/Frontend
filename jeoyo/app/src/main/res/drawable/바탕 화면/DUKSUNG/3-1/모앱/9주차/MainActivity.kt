package com.cookandroid.mydiary

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.DatePicker
import android.widget.EditText
import android.widget.Toast
import java.io.FileInputStream
import java.io.IOException
import java.util.*

class MainActivity : AppCompatActivity() {
    lateinit var dp : DatePicker
    lateinit var edtDiary : EditText
    lateinit var btnWrite : Button
    lateinit var fileName : String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        title = "간단 일기장"

        dp = findViewById(R.id.datePicker1)
        edtDiary = findViewById(R.id.edtDiary)
        btnWrite = findViewById(R.id.btnWrite)

        var cal = Calendar.getInstance()
        var cYear = cal.get(Calendar.YEAR)
        var cMonth = cal.get(Calendar.MONTH) //1~12월 => 0~11
        var cDay = cal.get(Calendar.DAY_OF_MONTH)

        fileName = (Integer.toString(cYear)+"_"
                + Integer.toString(cMonth+1)+"_"
                + Integer.toString(cDay) +".txt")
        var str = readDiary(fileName)
        edtDiary.setText(str)

        dp.init(cYear, cMonth, cDay){ view, year, monthOfYear, dayOfMonth ->
            fileName = (Integer.toString(year)+"_"
                    + Integer.toString(monthOfYear)+"_"
                    + Integer.toString(dayOfMonth) +".txt")
            var str = readDiary(fileName)
            edtDiary.setText(str)
        }

        btnWrite.setOnClickListener {
            //파일 쓰기
            var outFs = openFileOutput(fileName, Context.MODE_PRIVATE)
            var str = edtDiary.text.toString()
            outFs.write(str.toByteArray())
            outFs.close()
            Toast.makeText(applicationContext, "$fileName 이 저장됨", Toast.LENGTH_SHORT).show()
        }
    }
    fun readDiary(fName:String) : String? {
        var diaryStr : String? = null
        var inFs : FileInputStream
        try{
            inFs = openFileInput(fName)
            var txt = ByteArray(500)
            inFs.read(txt)
            inFs.close()
            diaryStr=txt.toString(Charsets.UTF_8).trim()
            btnWrite.text="수정 하기"
        }catch(e: IOException){
            var inputS = resources.openRawResource(R.raw.android12)
            var txt = ByteArray(inputS.available())
            inputS.read(txt)

            edtDiary.hint=txt.toString(Charsets.UTF_8)
            btnWrite.text="새로 저장"
            inputS.close()
        }
        return diaryStr
    }
}