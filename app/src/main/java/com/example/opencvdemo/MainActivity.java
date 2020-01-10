package com.example.opencvdemo;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo._01.GrayActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView mSampleText;
    private Button mButton1;
    private Button mButton2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(NativeUtils.stringFromJNI());
    }



    private void initView() {
        mSampleText = (TextView) findViewById(R.id.sample_text);
        mButton1 = (Button) findViewById(R.id.button1);
        mButton2 = (Button) findViewById(R.id.button2);

        mButton1.setOnClickListener(this);
        mButton2.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button1:
                startActivity(new Intent(this, GrayActivity.class));
                break;
            case R.id.button2:



                break;
        }
    }
}
