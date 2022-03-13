package com.cookandroid.mydialog

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.RadioGroup
import android.widget.TextView
import androidx.appcompat.app.AlertDialog
import com.google.android.material.snackbar.Snackbar

class MainActivity : AppCompatActivity() {
    lateinit var tvName : TextView
    lateinit var tvEmail : TextView
    lateinit var button1 : Button
    lateinit var dlgEdtName : EditText
    lateinit var dlgEdtEmail : EditText
    lateinit var rdoGroup : RadioGroup

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        title="사용자 정보 입력"

        tvName = findViewById<TextView>(R.id.tvName)
        tvEmail = findViewById(R.id.tvEmail)
        button1 = findViewById(R.id.button1)

        button1.setOnClickListener {
            var dlg = AlertDialog.Builder(this@MainActivity)

            var dialogView = View.inflate(this@MainActivity, R.layout.dialog1, null)
            dlg.setView(dialogView)
            dlg.setTitle("사용자 정보 입력")
            dlg.setPositiveButton("확인"){ dialog, which ->
                dlgEdtName = dialogView.findViewById<EditText>(R.id.dlgEdt1)
                dlgEdtEmail = dialogView.findViewById(R.id.dlgEdt2)
                tvName.text = dlgEdtName.text.toString()
                tvEmail.text=dlgEdtEmail.text.toString()

                rdoGroup = dialogView.findViewById(R.id.rGroup)
                when(rdoGroup.checkedRadioButtonId){
                    R.id.rdo3 -> tvName.text = dlgEdtName.text.toString() + " 3학년"
                    R.id.rdo4 -> tvName.text = dlgEdtEmail.text.toString() + " 4학년"
                    else -> Snackbar.make(it, "학년을 먼저 선택하세요", Snackbar.LENGTH_LONG).show()
                }
            }
            dlg.setNegativeButton("취소") { dialog, which ->
                Snackbar.make(it, "취소했습니다", Snackbar.LENGTH_LONG).show()
            }
                dlg.show()
            }
        }
    }
