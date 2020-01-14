package com.example.opencvdemo._06;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo.NativeUtils;
import com.example.opencvdemo.R;

public class CustomActivity extends AppCompatActivity {

    private ImageView mImageView1;
    private ImageView mImageView2;
    private ImageView mImageView3;
    private ImageView mImageView4;
    private ImageView mImageView5;
    private ImageView mImageView6;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_custom);
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
    }


    private void initData() {
        mImageView1.setImageResource(R.drawable.ic);

        Bitmap bitmap2 = getBitmap();
        NativeUtils.filter2D_robert(bitmap2);
        mImageView2.setImageBitmap(bitmap2);

        Bitmap bitmap3 = getBitmap();
        NativeUtils.filter2D_soble_left(bitmap3);
        mImageView3.setImageBitmap(bitmap3);

        Bitmap bitmap4 = getBitmap();
        NativeUtils.filter2D_soble_right(bitmap4);
        mImageView4.setImageBitmap(bitmap4);

        Bitmap bitmap5 = getBitmap();
        NativeUtils.filter2D_soble_right(bitmap5);
        mImageView5.setImageBitmap(bitmap5);
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
