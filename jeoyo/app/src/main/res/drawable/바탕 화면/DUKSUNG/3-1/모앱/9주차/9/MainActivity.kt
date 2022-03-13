package com.cookandroid.mysqlite

import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteException
import android.database.sqlite.SQLiteOpenHelper
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class MainActivity : AppCompatActivity() {
    lateinit var edtName:EditText
    lateinit var edtNumber:EditText
    lateinit var edtNameResult:EditText
    lateinit var edtNumberResult:EditText
    lateinit var btnInit:Button
    lateinit var btnInsert:Button
    lateinit var btnSelect:Button
    lateinit var btnUpdate : Button
    lateinit var btnDelete : Button

    lateinit var myHelper : myDBHelper
    lateinit var sqlDB : SQLiteDatabase
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        title = "가수 그릅 관리 DB"

        edtName = findViewById(R.id.edtName)
        edtNumber = findViewById(R.id.edtNumber)
        edtNameResult = findViewById(R.id.edtNameResult)
        edtNumberResult = findViewById(R.id.edtNumberResult)

        btnInit = findViewById(R.id.btnInit)
        btnInsert = findViewById(R.id.btnInsert)
        btnSelect = findViewById(R.id.btnSelect)
        btnDelete = findViewById(R.id.btnDelete)
        btnUpdate = findViewById(R.id.btnUpdate)

        myHelper = myDBHelper(this)

        btnInit.setOnClickListener {
            sqlDB = myHelper.writableDatabase
            myHelper.onUpgrade(sqlDB, 1, 2)
            sqlDB.close()
            Toast.makeText(applicationContext, "초기화됨", Toast.LENGTH_SHORT).show()
        }

        btnInsert.setOnClickListener {
            sqlDB = myHelper.writableDatabase
            try {
                //INSERT INTO groupTBL VALUES('bts' 7);
                //edtName.text, edtNumber.text
                sqlDB.execSQL(
                    "INSERT INTO groupTBL VALUES('"
                            + edtName.text.toString() + "', " + edtNumber.text.toString() + ");"
                );
            } catch(e:SQLiteException){
                e.printStackTrace()
            } finally {
                sqlDB.close()
            }
            Toast.makeText(applicationContext, "입력됨", Toast.LENGTH_SHORT).show()
            btnSelect.callOnClick()
        }

        btnUpdate.setOnClickListener {
            sqlDB = myHelper.writableDatabase
            try{
                if(edtName.getText().toString() != ""){
                    // UPDATE groupTBL SET gNumber=7 WHERE gName = 'bst';
                    sqlDB.execSQL("UPDATE groupTBL SET gNumber=" + edtNumber.getText() +
                            "WHERE gName='"+edtName.getText().toString()+"';")
                }
            } catch(e:SQLiteException){
                e.printStackTrace()
            } finally{
                sqlDB.close()
            }
            Toast.makeText(applicationContext, "수정됨", Toast.LENGTH_SHORT).show()
        }

        btnDelete.setOnClickListener {
            sqlDB = myHelper.writableDatabase
            try{
                if(edtName.getText().toString() != ""){
                    // DELETE FROM groupTBL WHERE gName = 'bts';
                    sqlDB.execSQL("DELETE FROM groupTBL WHERE gName = '" +
                            edtName.getText().toString()+"';")
                }
            } catch(e:SQLiteException){
                e.printStackTrace()
            } finally{
                sqlDB.close()
            }
            Toast.makeText(applicationContext, "삭제됨", Toast.LENGTH_SHORT).show()
            btnSelect.callOnClick()
        }

        btnSelect.setOnClickListener {
            sqlDB = myHelper.readableDatabase
            try {
                var cursor: Cursor
                cursor = sqlDB.rawQuery("SELECT * FROM groupTBL;", null)

                var strNames = ""
                var strNumbers = ""
                while (cursor.moveToNext()) {
                    //cursor.getString(0), cursor.getInt(1)
                    strNames += cursor.getString(0) + "\r\n"
                    strNumbers += cursor.getString(1) + "\r\n"
                }
                Toast.makeText(applicationContext, "조회됨", Toast.LENGTH_SHORT).show()
                edtNameResult.setText(strNames)
                edtNumberResult.setText(strNumbers)
                cursor.close()
            } catch(e:SQLiteException){
                e.printStackTrace()
            } finally {
                sqlDB.close()
            }


            sqlDB.close()

        }
    }

    inner class myDBHelper(context : Context) : SQLiteOpenHelper(context, "groupDB", null, 1){
        override fun onCreate(db: SQLiteDatabase?) {
            db!!.execSQL("CREATE TABLE groupTBL (gName CHAR(20) PRIMARY KEY, gNumber INTEGER);")
        }

        override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
            db!!.execSQL("DROP TABLE IF EXISTS groupTBL")
            onCreate(db)
        }
    }
}