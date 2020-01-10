package com.example.opencvdemo._01;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo.NativeUtils;
import com.example.opencvdemo.R;

public class GrayActivity extends AppCompatActivity {

    private ImageView mImageView1;
    private ImageView mImageView2;
    private ImageView mImageView3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gray);
        initView();
        initData();
    }

    private void initData() {
        mImageView1.setImageResource(R.drawable.ic);

        {
            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inMutable = true;
            //最好的是ARGB8888 32位
            options.inPreferredConfig = Bitmap.Config.RGB_565;
            // RGB_565比ARGB_8888小1 倍
            // ARGB_8888 -> RGB 565 RGB 5位R 6位G 5位B   565是16位
            Bitmap src = BitmapFactory.decodeResource(getResources(), R.drawable.ic, options);
            mImageView2.setImageBitmap(BitmapUtils.gray(src));
        }
        {
            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inMutable = true;
            //最好的是ARGB8888 32位
            options.inPreferredConfig = Bitmap.Config.RGB_565;
            // RGB_565比ARGB_8888小1 倍
            // ARGB_8888 -> RGB 565 RGB 5位R 6位G 5位B   565是16位
            Bitmap src = BitmapFactory.decodeResource(getResources(), R.drawable.ic, options);
            NativeUtils.gray(src);
            mImageView3.setImageBitmap(src);
        }
    }

    private void initView() {
        mImageView1 = (ImageView) findViewById(R.id.imageView1);
        mImageView2 = (ImageView) findViewById(R.id.imageView2);
        mImageView3 = (ImageView) findViewById(R.id.imageView3);
    }
}
