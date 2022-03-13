package com.cookandroid.mynavermovie

import android.graphics.Movie
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import io.reactivex.Single
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers
import kotlinx.android.synthetic.main.activity_main.*
import org.jsoup.Jsoup
import org.jsoup.select.Elements
import java.lang.Exception

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        startButton.setOnClickListener {
            listview.layoutManager = LinearLayoutManager(this)
            doTask("https://movie.naver.com/movie/running/current.nhn?order?reverse")

        }
    }

    fun doTask(myurl: String) {
        var documentTitle: String = ""
        var itemList: ArrayList<MovieItem> = arrayListOf()
        Single.fromCallable {
            try {
                val doc = Jsoup.connect(myurl).get()

                val elems: Elements = doc.select("ul.lst_detail_t1 li")
                run elemsLoop@{
                    elems.forEachIndexed { index, elem ->
                        var title = elem.select("dt.tit a").text()
                        var score1 = elem.select("dl.info_star div.star_t1 span.num").text()
                        var score2 = elem.select("span.num2").text()
                        var reserve = elem.select("dl.info_exp div.star_t1 span.num").text()
                        var imgsrc = elem.select("div.thumb a img").attr("src")
                        var item = MovieItem(title, score1, score2, reserve, imgsrc)
                        itemList.add(item)
                        if (index == 9) {
                            return@elemsLoop
                        }
                    }
                }
                documentTitle = doc.title()
            } catch (e: Exception) {
                e.printStackTrace()
            }
            return@fromCallable documentTitle
        }
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
            .subscribe({ text ->
               //showData(text.toString())
                //showData(itemList.joinToString())
                listview.adapter = MovieItemAdapter(itemList)
            }, {
                it.printStackTrace()
            })
    }

    /*
        fun showData(message: String) {
            output1.append(message + "\n")
        }

     */
    }

