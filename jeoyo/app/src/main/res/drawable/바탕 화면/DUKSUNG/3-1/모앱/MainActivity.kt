package com.cookandroid.mymp3player

import android.content.Context
import android.media.MediaPlayer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.os.SystemClock
import android.view.View
import android.widget.*
import androidx.core.app.ActivityCompat
import java.io.File
import java.io.FileInputStream
import java.text.SimpleDateFormat

class MainActivity : AppCompatActivity() {
    var listViewMP3:ListView? = null
    lateinit var btnPlay:Button
    lateinit var btnPause:Button
    lateinit var btnStop:Button
    lateinit var tvMP3: TextView
    lateinit var tvTime: TextView
    lateinit var pbMP3:SeekBar

    lateinit var mp3List:ArrayList<String>
    lateinit var selectedMP3:String

    lateinit var mPlayer : MediaPlayer

    var mp3Path = Environment.getExternalStorageDirectory().path + "/"
    var PAUSE = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        title = "간단 MP3 플레이어"
        ActivityCompat.requestPermissions(this, arrayOf(android.Manifest.permission.WRITE_EXTERNAL_STORAGE), Context.MODE_PRIVATE)

        mp3List = ArrayList()
        var fileName : String
        var extName : String
        var listFiles = File(mp3Path).listFiles()
        for(file in listFiles){
            fileName = file.name
            extName = fileName.substring(fileName.length-3)
            if(extName == "mp3")
                mp3List.add(fileName)
        }
        var listViewMP3 = findViewById<ListView>(R.id.listViewMP3)
        var adapter = ArrayAdapter(this, android.R.layout.simple_list_item_single_choice, mp3List)
        listViewMP3.choiceMode = ListView.CHOICE_MODE_SINGLE
        listViewMP3.adapter = adapter
        listViewMP3.setItemChecked(0, true)
        selectedMP3 = mp3List[0]
        listViewMP3.setOnItemClickListener{ arg0, arg1, arg2, arg3 ->
            selectedMP3 = mp3List[arg2]
        }

        btnPlay = findViewById(R.id.btnPlay)
        btnPause = findViewById(R.id.btnPause)
        btnStop = findViewById(R.id.btnStop)
        tvMP3 = findViewById(R.id.tvMP3)
        tvTime = findViewById(R.id.tvTime)
        pbMP3 = findViewById(R.id.pbMP3)

        btnPlay.setOnClickListener {
            val fis = FileInputStream(mp3Path+selectedMP3)
            mPlayer = MediaPlayer()
            mPlayer.setDataSource(fis.fd)
            mPlayer.prepare()
            mPlayer.start()
            btnPlay.isClickable = false
            btnStop.isClickable = true
            btnPause.isClickable=true
            tvMP3.text="실행중인 음악 : $selectedMP3"
            pbMP3.visibility= View.VISIBLE


            object:Thread(){
                var timeFormat = SimpleDateFormat("mm:ss")
                override fun run(){
                    if(mPlayer == null)
                        return
                    pbMP3.max = mPlayer.duration
                    while(mPlayer.isPlaying){
                        runOnUiThread{
                            pbMP3.progress=mPlayer.currentPosition
                            tvTime.text = "진행 시간 : "+timeFormat.format(mPlayer.currentPosition)
                        }
                        SystemClock.sleep(200)
                    }
                }
            }.start()
        }
        btnPause.isClickable=false
        btnPause.setOnClickListener {
            // 재생 -> 일시정지
            if(PAUSE == false){
                mPlayer.pause()
                btnPause.text="이어듣기"
                PAUSE = true
               // pbMP3.visibility = View.INVISIBLE
            }
            // 일시정지 -> 이어듣기
            else{
                mPlayer.start()
                btnPause.text="일시정지"
                PAUSE = false
                //pbMP3.visibility=View.VISIBLE
                object:Thread(){
                    var timeFormat = SimpleDateFormat("mm:ss")
                    override fun run(){
                        if(mPlayer == null)
                            return
                        pbMP3.max = mPlayer.duration
                        while(mPlayer.isPlaying){
                            runOnUiThread{
                                pbMP3.progress=mPlayer.currentPosition
                                tvTime.text = "진행 시간 : "+timeFormat.format(mPlayer.currentPosition)
                            }
                            SystemClock.sleep(200)
                        }
                    }
                }.start()
            }
        }

        btnStop.isClickable=false
        btnStop.setOnClickListener {
            mPlayer.stop()
            mPlayer.reset()
            btnPlay.isClickable=true
            btnStop.isClickable=false
            tvMP3.text="실행중인 음악 : "
            tvTime.text="진행 시간 : "
            pbMP3.visibility=View.INVISIBLE
            btnPause.isClickable=false
            btnPause.text="일시정지"
        }

    }
}