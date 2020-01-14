package com.example.opencvdemo._05;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo.NativeUtils;
import com.example.opencvdemo.R;

public class CodeActivity extends AppCompatActivity {

    private ImageView mImageView1;
    private ImageView mImageView2;
    private ImageView mImageView3;
    private ImageView mImageView4;
    private ImageView mImageView5;
    private ImageView mImageView6;
    private ImageView mImageView7;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_code);
        initView();
        initData();
    }

    private void initView() {
        mImageView1 = (ImageView) findViewById(R.id.imageView1);
        mImageView2 = (ImageView) findViewById(R.id.imageView2);
        mImageView3 = (ImageView) findViewById(R.id.imageView3);
        mImageView4 = (ImageView) findViewById(R.id.imageView4);
        mImageView5 = (ImageView) findViewById(R.id.imageView5);
        mImageView6 = (ImageView) findViewById(R.id.imageView6);
        mImageView7 = (ImageView) findViewById(R.id.imageView7);
    }

    private void initData() {
        mImageView1.setImageResource(R.drawable.ic);

        Bitmap bitmap2 = getBitmap();
        NativeUtils.morphologyEx(bitmap2);
        mImageView2.setImageBitmap(bitmap2);

        Bitmap bitmap3 = getBitmap();
        NativeUtils.morphologyEx2(bitmap3);
        mImageView3.setImageBitmap(bitmap3);

        Bitmap bitmap4 = getBitmap();
        NativeUtils.morphologyEx3(bitmap4);
        mImageView4.setImageBitmap(bitmap4);

        Bitmap bitmap5 = getBitmap();
        NativeUtils.extractionLine(bitmap5);
        mImageView5.setImageBitmap(bitmap5);

        Bitmap bitmap6 = getBitmap();
        NativeUtils.pyrUp(bitmap6);
        mImageView6.setImageBitmap(bitmap6);

        Bitmap bitmap7 = getBitmap();
        NativeUtils.pyrDown(bitmap7);
        mImageView7.setImageBitmap(bitmap7);
    }

    private Bitmap getBitmap() {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inMutable = true;
        //最好的是ARGB8888 32位
        options.inPreferredConfig = Bitmap.Config.RGB_565;
        // RGB_565比ARGB_8888小1 倍
        // ARGB_8888 -> RGB 565 RGB 5位R 6位G 5位B   565是16位
        return BitmapFactory.decodeResource(getResources(), R.drawable.ic, options);
    }
}
