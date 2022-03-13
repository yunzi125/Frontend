package com.cookandroid.mygmap

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Looper
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.TextView
import com.google.android.gms.location.*
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.BitmapDescriptorFactory
import com.google.android.gms.maps.model.GroundOverlayOptions
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions
import com.yanzhenjie.permission.AndPermission
import com.yanzhenjie.permission.runtime.Permission

class MainActivity : AppCompatActivity(), OnMapReadyCallback {
    private lateinit var mMap : GoogleMap
    private lateinit var  videoMark : GroundOverlayOptions
    lateinit var tv : TextView
    lateinit var btn : Button
    var locationClient: FusedLocationProviderClient? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tv = findViewById<TextView>(R.id.mypos)
        btn = findViewById(R.id.btnPos)

        btn.setOnClickListener {
            requestLocation()
        }
        AndPermission.with(this)
                .runtime()
                .permission(Permission.Group.LOCATION)
                .onGranted{ permissions->
                    Log.d("Main", "허용된 권한 갯수 : ${permissions.size}")
                }
                .onDenied{ permissions->
                    Log.d("Main", "거부된 권한 갯수 : ${permissions.size}")
                }
                .start()

        val mapFragment = supportFragmentManager.findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(this)
    }


    private fun requestLocation(){
        locationClient = LocationServices.getFusedLocationProviderClient(this)
        try{
            locationClient?.lastLocation?.addOnSuccessListener { location ->
                if(location == null){
                    tv.setText("최근 위치 확인 실패")
                }
                else{
                    tv.setText("최근 위치 확인 성공 : ${location.latitude}, ${location.longitude}")
                }
            }
                    ?.addOnFailureListener {
                        tv.setText("최근 위치 확인 시 에러 : ${it.message}")
                        it.printStackTrace()
                    }
            val locationRequest = LocationRequest.create()
            locationRequest.run{
                priority = LocationRequest.PRIORITY_HIGH_ACCURACY
                interval = 60*1000
            }
            val locationCallback = object: LocationCallback(){
                override fun onLocationResult(p0: LocationResult?) {
                    p0?.let{
                        for((i, location) in it.locations.withIndex()){
                            tv.setText("내 위치 : ${location.latitude}, ${location.longitude}")
                        }
                    }
                }
            }
            locationClient?.requestLocationUpdates(locationRequest, locationCallback, Looper.myLooper())
        }
        catch(e: SecurityException){
            e.printStackTrace()
        }
    }

    override fun onMapReady(p0: GoogleMap) {
        mMap = p0
        mMap.mapType = GoogleMap.MAP_TYPE_SATELLITE
        mMap.uiSettings.isZoomControlsEnabled = true
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(37.568256, 126.897240), 15f))
        mMap.setOnMapClickListener {point ->
            videoMark = GroundOverlayOptions().image(
                    BitmapDescriptorFactory.fromResource(R.drawable.presence_video_busy))
                            .position(point, 100f, 100f)
            mMap.addGroundOverlay(videoMark)
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)

        menu!!.add(0,1,0,"위성 사진")
        menu.add(0, 2, 0, "일반 사진")
        var smenu = menu.addSubMenu("장소 찾기>>")
        smenu.add(0, 4, 0, "덕성여자대학교")
        smenu.add(0,5,0,"월드컵경기장")
        smenu.add(0,6,0,"경포대")
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when(item.itemId){
            1 -> {mMap.mapType = GoogleMap.MAP_TYPE_SATELLITE

            return true}
            2 -> {
                mMap.mapType = GoogleMap.MAP_TYPE_NORMAL
                return true    }
            4 -> {mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(37.65129, 127.01612), 15f))
                mMap.addMarker(MarkerOptions().position(LatLng(37.65129, 127.01612)).title("덕성여자대학교"))
                return true}
            5 -> { mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(37.568256, 126.897240), 15f))
                mMap.addMarker(MarkerOptions().position(LatLng(37.568256, 126.897240)).title("월드컵 경기장"))
            return true}
            6 -> {mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(LatLng(37.79518, 128.89660), 15f))
                mMap.addMarker(MarkerOptions().position(LatLng(37.79518, 128.89660)).title("경포대"))
                return true}
        }
        return false
    }


}