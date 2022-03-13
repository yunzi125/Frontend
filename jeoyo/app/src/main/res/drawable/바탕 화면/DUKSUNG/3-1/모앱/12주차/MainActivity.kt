package org.techtown.myopenhospital

import android.os.AsyncTask
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.activity_main.*
import org.xmlpull.v1.XmlPullParser
import org.xmlpull.v1.XmlPullParserFactory
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.StringReader
import java.net.URL

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btnSearch.setOnClickListener {
            listview.layoutManager = LinearLayoutManager(this)

            val serviceUrl = "http://apis.data.go.kr/B551182/pubReliefHospService/getpubReliefHospList"
            val serviceKey = "HWThHSGb7F%2F2AI%2FYTnHCTY2krziEcp%2FHCmXzY3W2Nu5nNtO7unLq7ji8sjaAa7LP30Eodj6xkccLU4EifCs9Vg%3D%3D"
            // pageNo = 1&numOfRows = 10
            var spclAdmTyCd = ""
            when(rGroup.checkedRadioButtonId){
                R.id.A0 -> spclAdmTyCd="A0"
                R.id.a97 -> spclAdmTyCd="97"
                R.id.a99 -> spclAdmTyCd="99"
                else -> Toast.makeText(applicationContext, "병원 코드를 먼저 선택하세요", Toast.LENGTH_LONG).show()
            }

            val requestUrl = serviceUrl + "?serviceKey=" + serviceKey+"&pageNo=1&numOfRows=10&spclAdmTyCd="+spclAdmTyCd
            fetchXML(requestUrl)
        }
    }

    fun fetchXML(myURL:String){
        lateinit var page : String

        class getDangerGrade : AsyncTask<Void, Void, Void> (){
            override fun doInBackground(vararg p0: Void?): Void? { // url -> xml
                val stream = URL(myURL).openStream()
                val bufreader = BufferedReader(InputStreamReader(stream, "UTF-8"))
                var line = bufreader.readLine()
                page = ""
                while(line !=null){
                    page += line
                    line = bufreader.readLine()
                }
                return null
            }

            override fun onPostExecute(result: Void?) { // xml 파싱
                super.onPostExecute(result)
                var itemList:ArrayList<Hospital> = arrayListOf()
                var bSet1 = false
                var bSet2 = false
                var bSet3 = false
                var bSet4 = false
                lateinit var sgguNm : String
                lateinit var sidoNm : String
                lateinit var telno : String
                lateinit var yadmNm : String
                var factory = XmlPullParserFactory.newInstance()
                factory.setNamespaceAware(true)
                var xpp = factory.newPullParser() // XML 파서
                xpp.setInput(StringReader(page))
                var eventType = xpp.eventType
                while(eventType!= XmlPullParser.END_DOCUMENT){
                    if (eventType == XmlPullParser.START_DOCUMENT){}
                    else if(eventType == XmlPullParser.START_TAG){
                        var tag_name = xpp.name
                        if(tag_name.equals("sgguNm")) bSet1 = true
                        else if(tag_name.equals("sidoNm")) bSet2 = true
                        else if(tag_name.equals("telno")) bSet3 = true
                        else if(tag_name.equals("yadmNm")) bSet4 = true
                    }
                    if(eventType == XmlPullParser.TEXT) {
                        if(bSet1) {
                            sgguNm = xpp.text.toString()
                            bSet1 = false
                        }
                        else if(bSet2) {
                            sidoNm = xpp.text.toString()
                            bSet2 = false
                        }
                        else if(bSet3) {
                            telno = xpp.text.toString()
                            bSet3 = false
                        }
                        else if(bSet4) {
                            yadmNm = xpp.text.toString()
                            bSet4 = false
                            var item = Hospital(yadmNm, sidoNm+" "+sgguNm, telno)
                            itemList.add(item)
                        }
                    }
                    if(eventType == XmlPullParser.END_TAG){}
                    // itemList.add()
                    eventType = xpp.next()
                }
                listview.adapter = HospitalAdapter(itemList)
            }
        }

        getDangerGrade().execute()
    }
}