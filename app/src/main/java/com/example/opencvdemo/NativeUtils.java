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



    // 原始置灰色
    public static native void gray(Bitmap bitmap);



    // -------------  混合 start  --------------
    // 裁剪矩形框
    public static native void clip(Bitmap bitmap);
    // 系统方法置灰色
    public static native void gray2(Bitmap bitmap);
    // 遍历方法置灰色
    public static native void gray3(Bitmap bitmap);
    // 添加水印logo
    public static native void addLogo(Bitmap srcBitmap,Bitmap logoBitmap);
    // 添加滤镜
    public static native void filter(Bitmap bitmap);
    // -------------  混合 end  --------------


    // -------------  绘制 start  --------------
    public static native void draw(Bitmap bitmap);
    public static native void zeros(Bitmap bitmap);


    // -------------  绘制 end  --------------




}
