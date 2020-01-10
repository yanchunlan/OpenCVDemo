package com.example.opencvdemo;

import android.graphics.Bitmap;

/**
 * author:  ycl
 * date:  2020/01/10 10:24
 * desc:
 */
public class NativeUtils {

    static {
        System.loadLibrary("OpenCV");
    }


    public static native String stringFromJNI();

    public static native int gray(Bitmap bitmap);
}
