package com.example.opencvdemo;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo._01.GrayActivity;
import com.example.opencvdemo._02.MixActivity;
import com.example.opencvdemo._03.DrawActivity;
import com.example.opencvdemo._04.BeautyActivity;
import com.example.opencvdemo._05.CodeActivity;
import com.example.opencvdemo._06.CustomActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button mButton1;
    private Button mButton2;
    private Button mButton3;
    private Button mButton4;
    private Button mButton5;
    private Button mButton6;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(NativeUtils.stringFromJNI());
    }


    private void initView() {
        mButton1 = (Button) findViewById(R.id.button1);
        mButton2 = (Button) findViewById(R.id.button2);
        mButton3 = (Button) findViewById(R.id.button3);
        mButton4 = (Button) findViewById(R.id.button4);
        mButton5 = (Button) findViewById(R.id.button5);
        mButton6 = (Button) findViewById(R.id.button6);

        mButton1.setOnClickListener(this);
        mButton2.setOnClickListener(this);
        mButton3.setOnClickListener(this);
        mButton4.setOnClickListener(this);
        mButton5.setOnClickListener(this);
        mButton6.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button1: // 滤镜处理
                startActivity(new Intent(this, GrayActivity.class));
                break;
            case R.id.button2: // Mat对象与图像混合
                startActivity(new Intent(this, MixActivity.class));
                break;
            case R.id.button3: // 图像的绘制与卷积
                startActivity(new Intent(this, DrawActivity.class));
                break;
            case R.id.button4: // 图片美容
                startActivity(new Intent(this, BeautyActivity.class));
                break;
            case R.id.button5: // 验证码识别
                startActivity(new Intent(this, CodeActivity.class));
                break;
            case R.id.button6: // 自定义线性滤波
                startActivity(new Intent(this, CustomActivity.class));
                break;
        }
    }
}
