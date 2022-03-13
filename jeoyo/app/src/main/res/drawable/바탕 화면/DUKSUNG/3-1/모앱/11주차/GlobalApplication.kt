package com.cookandroid.mysnskakao

import android.app.Application
import com.kakao.sdk.common.KakaoSdk

class GlobalApplication : Application() {
    override fun onCreate() {
        super.onCreate()

        //카카오 sdk 초기화
        KakaoSdk.init(this, "d405ed9c1f08ebff09623580f22abafd")
    }
}