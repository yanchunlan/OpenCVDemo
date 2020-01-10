package com.example.opencvdemo._01;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;

/**
 * author:  ycl
 * date:  2020/01/10 10:03
 * desc:
 */
public class BitmapUtils {

    /**
     * 灰图是：
     * ColorMatrix colorMatrix = new ColorMatrix(new float[]{
     *                 0.213f,0.715f,0.072f,0,0,
     *                 0.213f,0.715f,0.072f,0,0,
     *                 0.213f,0.715f,0.072f,0,0,
     *                 0,0,0,1,0,
     *         });
     * 底图是：
     * ColorMatrix colorMatrix = new ColorMatrix(new float[]{
     *                 -1,0,0,0,255,
     *                 0,-1,0,0,255,
     *                 0,0,-1,0,255,
     *                 0,0,0,1,0,
     *         });
     */
    public static Bitmap opencv(Bitmap bitmap){
        Bitmap dst= Bitmap.createBitmap(bitmap.getWidth(),bitmap.getHeight(),bitmap.getConfig());
        Canvas canvas=new Canvas(dst);
        Paint paint=new Paint();
        paint.setAntiAlias(true);
        paint.setDither(true);
        ColorMatrix colorMatrix=new ColorMatrix();
        //饱和 0->灰度图
        colorMatrix.setSaturation(0);
        paint.setColorFilter(new ColorMatrixColorFilter(colorMatrix));
        canvas.drawBitmap(bitmap,0,0,paint);
        return dst;
    }

    public static Bitmap gray(Bitmap bitmap) {
        Bitmap dst = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), bitmap.getConfig());
        //java层像素操作
        int[] pixels = new int[bitmap.getWidth() * bitmap.getHeight()];
        //第二个参数偏移量
        bitmap.getPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());
        for (int i = 0; i < pixels.length; i++) {
            int pixel = pixels[i];
            int a = (pixel >> 24) & 0xff;
            int r = (pixel >> 16) & 0xff;
            int g = (pixel >> 8) & 0xff;
            int b = pixel & 0xff;
            // f=.0.213f*r+0.715f*g+0.072f*b;
            //灰度
            //int gery = (int) (0.213f * r + 0.715f * g + 0.072f * b);
            //黑白
            int gery = (a + r + g) / 3 > 125 ? 125 : 0;
            pixels[i] = (a << 24) | (gery << 16) | (gery << 8) | gery;
        }
        dst.setPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());
        return dst;
    }
}
