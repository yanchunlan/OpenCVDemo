package com.example.opencvdemo._02;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.opencvdemo.NativeUtils;
import com.example.opencvdemo.R;

public class MixActivity extends AppCompatActivity {

    private ImageView mImageView1;
    private ImageView mImageView2;
    private ImageView mImageView3;
    private ImageView mImageView4;
    private ImageView mImageView5;
    private ImageView mImageView6;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mix);
        initView();
        initData();
    }

    private void initData() {
        mImageView1.setImageResource(R.drawable.ic);

        mImageView2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Bitmap bitmap2 = getBitmap();
                NativeUtils.clip(bitmap2);
                mImageView2.setImageBitmap(bitmap2);
            }
        });
        mImageView3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Bitmap bitmap3 = getBitmap();
                NativeUtils.gray2(bitmap3);
                mImageView3.setImageBitmap(bitmap3);
            }
        });
        mImageView4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Bitmap bitmap4 = getBitmap();
                NativeUtils.gray3(bitmap4);
                mImageView4.setImageBitmap(bitmap4);
            }
        });
        mImageView5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               /* Bitmap bitmap = getBitmap();
                Bitmap logoBitmap = getLogoBitmap();
                try {
                    NativeUtils.addLogo(bitmap, logoBitmap);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                mImageView5.setImageBitmap(bitmap);*/
            }
        });
        mImageView6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                /*Bitmap bitmap = getBitmap();
                NativeUtils.filter(bitmap);
                mImageView6.setImageBitmap(bitmap);*/
            }
        });
    }

    private void initView() {
        mImageView1 = (ImageView) findViewById(R.id.imageView1);
        mImageView2 = (ImageView) findViewById(R.id.imageView2);
        mImageView3 = (ImageView) findViewById(R.id.imageView3);
        mImageView4 = (ImageView) findViewById(R.id.imageView4);
        mImageView5 = (ImageView) findViewById(R.id.imageView5);
        mImageView6 = (ImageView) findViewById(R.id.imageView6);
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

    private Bitmap getLogoBitmap() {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inMutable = true;
        //最好的是ARGB8888 32位
        options.inPreferredConfig = Bitmap.Config.RGB_565;
        // RGB_565比ARGB_8888小1 倍
        // ARGB_8888 -> RGB 565 RGB 5位R 6位G 5位B   565是16位
        return BitmapFactory.decodeResource(getResources(), R.mipmap.ic_launcher, options);
    }
}
