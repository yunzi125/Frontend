package org.androidtown.jeoyo.fragment;

import android.content.Intent;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import org.androidtown.jeoyo.R;
import org.androidtown.jeoyo.activity.HomeGongActivity;

public class HomeFragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_home, container, false);
        View gong_next = view.findViewById(R.id.gong_next);
        View dae_next = view.findViewById(R.id.dae_next);
        View people_next = view.findViewById(R.id.people_next);
        View study_next = view.findViewById(R.id.study_next);

        gong_next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(view.getContext(), HomeGongActivity.class);
                startActivity(intent);    //intent 에 명시된 액티비티로 이동
            }
        });
    return view;
    }
}
