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
    // 图形绘制，直线，矩形，椭圆，圆，填充，文字
    public static native void draw(Bitmap bitmap);
    // 卷积操作
    public static native void zeros(Bitmap bitmap);
    // 系统的方法 - 均值模糊
    public static native void blur(Bitmap bitmap);
    // 系统的方法 - 高斯模糊
    public static native void gaussianBlur(Bitmap bitmap);
    // 系统的方法 - 中值模糊（对所有考虑的点进行排序，取中间的值）
    public static native void medianBlur(Bitmap bitmap);
    // -------------  绘制 end  --------------


    // -------------  美容 start  --------------
    // 系统的方法 - 中值模糊+掩膜
    public static native void medianBlur2(Bitmap bitmap);
    // 美容，高斯模糊+双边保留轮廓
    public static native void bilateralFilter(Bitmap bitmap);
    // 处理黑白图片，erode：腐蚀,最小值
    public static native void erode(Bitmap bitmap);
    // 处理黑白图片，dilate：膨胀，最大值
    public static native void dilate(Bitmap bitmap);
    // -------------  美容 end  --------------


    // -------------  验证码识别 start  --------------
    // 形体学操作:morphologyEx，仅仅学习
    public static native void morphologyEx(Bitmap bitmap);
    // 验证码识别
    // 方法一: 先闭图像后开图像
    public static native void morphologyEx2(Bitmap bitmap);
    // 方法二：彩色变成黑白再处理
    public static native void morphologyEx3(Bitmap bitmap);
    // 提取水平线/垂直线
    public static native void extractionLine(Bitmap bitmap);
    // 上采样：pyrUp
    public static native void pyrUp(Bitmap bitmap);
    // 降采样：pyrDown
    public static native void pyrDown(Bitmap bitmap);
    // -------------  验证码识别 end  --------------


    // -------------  自定义线性滤波 start  --------------
    // Robert算子
    public static native void filter2D_robert(Bitmap bitmap);
    // 左边算子
    public static native void filter2D_soble_left(Bitmap bitmap);
    // 右边算子
    public static native void filter2D_soble_right(Bitmap bitmap);
    // 拉普拉斯算子
    public static native void filter2D_laplace(Bitmap bitmap);
    // 自定义卷积实现模糊
    public static native void filter2D_custom(Bitmap bitmap);
    // 二值化
    public static native void threshold(Bitmap bitmap);
    // -------------  自定义线性滤波 end  --------------
}
