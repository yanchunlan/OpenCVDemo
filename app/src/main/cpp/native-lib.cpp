#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "utils.h"

/**
 * 一般此处的异常都是宽高，通道数量不一致导致的异常
 */
void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg) {
    // 查找异常类
    jclass cls = env->FindClass(name);
    /* 如果这个异常类没有找到，VM会抛出一个NowClassDefFoundError异常 */
    if (cls != NULL) {
        env->ThrowNew(cls, msg);  // 抛出指定名字的异常
    }
    /* 释放局部引用 */
    env->DeleteLocalRef(cls);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_opencvdemo_NativeUtils_stringFromJNI(JNIEnv *env, jclass clazz) {
    std::string hello = "OpenCV Demo";
    return env->NewStringUTF(hello.c_str());
}

/**
 * bitmap 直接获取指针，再对指针操作
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_gray(JNIEnv *env, jclass clazz, jobject bitmap) {

    AndroidBitmapInfo info;
    int res = AndroidBitmap_getInfo(env, bitmap, &info);

    if (res != 0) {
        return;
    }
    void *addrPtr;
    AndroidBitmap_lockPixels(env, bitmap, &addrPtr);
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        for (int i = 0; i < info.width * info.height; ++i) {
            //+i移动指针
            uint32_t *pixel_p = reinterpret_cast<uint32_t *>(addrPtr) + i;
            uint32_t pixel = *pixel_p;

            int a = (pixel >> 24) & 0xff;
            int r = (pixel >> 16) & 0xff;
            int g = (pixel >> 8) & 0xff;
            int b = pixel & 0xff;
            // f = 0.213f * r + 0.715f * g + 0.072f * b
            int gery = (int) (0.213f * r + 0.715f * g + 0.072f * b);
            //重新设置回去
            *pixel_p = (a << 24) | (gery << 16) | (gery << 8) | gery;

        }
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        for (int i = 0; i < info.width * info.height; ++i) {
            uint16_t *pixel_p = reinterpret_cast<uint16_t *>(addrPtr) + i;
            uint16_t pixel = *pixel_p;
            //5 0001 1111->1f
            //6 0011 1111->3f
            int r = ((pixel >> 11) & 0x1f) << 3;//8->5
            int g = ((pixel >> 5) & 0x3f) << 2;//8->6
            int b = (pixel & 0x1f) << 3;//8->5
            // f = 0.213f * r + 0.715f * g + 0.072f * b
            int gery = (int) (0.213f * r + 0.715f * g + 0.072f * b);
            //重新设置回去
            *pixel_p = ((gery >> 3) << 11) | ((gery >> 2) << 5) | (gery >> 3);
        }
    }
    AndroidBitmap_unlockPixels(env, bitmap);
}

/**
 * bitmap转换为mat，再对mat进行操作
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_clip(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat mat = bitmap2Mat(env, bitmap);
    //区域裁剪  bitmap -> mat -> mat遍历修改 -> bitmap
    Mat clip = mat(Rect(20, 20, 100, 100));
    int rows = clip.rows;
    int cols = clip.cols;
    LOGE("cols:%d,rows:%d", cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //获取像素 Vec3b表示3个参数
            int b = clip.at<Vec3b>(i, j)[0];
            int g = clip.at<Vec3b>(i, j)[1];
            int r = clip.at<Vec3b>(i, j)[2];
            //修改像素(底片效果)
            clip.at<Vec3b>(i, j)[0] = 255 - b;
            clip.at<Vec3b>(i, j)[1] = 255 - g;
            clip.at<Vec3b>(i, j)[2] = 255 - r;
        }
    }
    mat2bitmap(env, clip, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_gray2(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat mat = bitmap2Mat(env, bitmap);
    int rows = mat.rows;
    int cols = mat.cols;
    int channels = mat.channels();
    LOGE("转变前的：高：%d,宽：%d,通道:%d", rows, cols, channels);
    Mat gray;
    // bitmap里面转的是4通道
    //一个通道就可以代笔灰度
    cvtColor(mat, gray, COLOR_BGR5652GRAY);
    int grows = gray.rows;
    int gcols = gray.cols;
    int gchannels = gray.channels();
    LOGE("转变后的：高：%d,宽：%d,通道:%d", grows, gcols, gchannels);
    mat2bitmap(env, gray, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_gray3(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat mat = bitmap2Mat(env, bitmap);
    int rows = mat.rows;
    int cols = mat.cols;
    int channels = mat.channels();
    LOGE("转变前的：高：%d,宽：%d,通道:%d", rows, cols, channels);
    Mat gray(rows, cols, CV_8UC1);
    // bitmap里面转的是4通道
    //一个通道就可以代笔灰度
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //获取像素 Vec3b表示3个参数
            int b = mat.at<Vec3b>(i, j)[0];
            int g = mat.at<Vec3b>(i, j)[1];
            int r = mat.at<Vec3b>(i, j)[2];

            gray.at<uchar>(i, j) = 0.59 * g + 0.11 * r + 0.3 * b;
        }
    }
    int grows = gray.rows;
    int gcols = gray.cols;
    int gchannels = gray.channels();
    LOGE("转变后的：高：%d,宽：%d,通道:%d", grows, gcols, gchannels);
    mat2bitmap(env, gray, bitmap);
}

/**
 * 图片添加logo
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_addLogo(JNIEnv *env, jclass clazz, jobject src_bitmap,
                                                jobject logo_bitmap) {
    Mat src = bitmap2Mat(env, src_bitmap);
    LOGE("src_bitmap：高：%d,宽：%d,通道:%d", src.rows, src.cols, src.channels());
    Mat logoMat = bitmap2Mat(env, logo_bitmap);
    LOGE("logo_bitmap：高：%d,宽：%d,通道:%d", logoMat.rows, logoMat.cols, logoMat.channels());

    //非常生硬
//    add(mat,logoMat,dst);
    //需要保证两个图片大小一致而且
    //Mat dst;
//    addWeighted(src,0.7,logoMat,0.3,0.0,dst);

    //非要加一个小的图片logo
    Mat srcClip = src(Rect(0, 0, logoMat.cols, logoMat.rows));

    // todo 通道不一样导致有异常出现
    /*
    Mat canny;
    cvtColor(srcClip, canny, CV_BGR2GRAY);
    Canny(canny, canny, logoMat.cols,logoMat.rows);
    cvtColor(canny, canny, CV_GRAY2BGR);*/

    /**
        第一个参数：InputArray类型的src,表示需要加权的第一个数组，常常填一个Mat
        第二个参数：alpha，表示一个数组的权重
        第三个参数：src2表示第二个数组，它需要和第一个数组拥有相同的尺寸和像素
        第四个参数：beta,表示第二数组的权重值
        第五个参数：gamma，一个加到权重总和上的标量值
        第六个参数：dst，输出的数组，它和输入的两个数组拥有相同的尺寸和通道数
        第七个参数：dtype，输出阵列的可选深度，默认值-1，当两个数组具有相同的深度的时候，这个参数设置为-1，即等同于src1.depth()
     */
    //不适合加水印，只适合图片混合
    addWeighted(srcClip, 0, logoMat, 1, 0, srcClip);
    mat2bitmap(env, src, src_bitmap);
    JNU_ThrowByName(env, "java/lang/Exception", "addWeighted == null");
}

/**
 * 滤镜处理
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_filter(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    int rows = src.rows;
    int cols = src.cols;
    int alpha = 2;
    int beta = 1;
    /**
        饱和度:图片更多饱和，淡红，红色，鲜红，红的发紫等等,越饱和，颜色越深
        亮度:亮暗的程度
        对比度：最亮的和最暗的对比
        alpha 饱和度和对比度
        beat 亮度
        F(R)=alphaR+beta;
        F(G)=alphaG+beta;
        F(B)=alpha*B+beta;
    */
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int b = src.at<Vec3b>(i, j)[0];
            int g = src.at<Vec3b>(i, j)[1];
            int r = src.at<Vec3b>(i, j)[2];

            src.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(b * alpha + beta);
            src.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(g * alpha + beta);
            src.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(r * alpha + beta);
        }
    }
    mat2bitmap(env, src, bitmap);
    JNU_ThrowByName(env, "java/lang/Exception", "addWeighted == null");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_draw(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    line(src, Point(100, 200), Point(200, 200), Scalar(255, 255, 0), 2, LINE_8);

    rectangle(src, Point(100, 100), Point(200, 200), Scalar(0, 0, 255), 2, LINE_8);

    //第二个是椭圆的中心点
    //第三个参数，椭圆的大小 第一个参数宽，第二个参数高
    //第四个参数：旋转度数
    ellipse(src, Point(src.cols / 2, src.rows / 2), Size(src.cols / 8, src.rows / 4), 180, 0, 360,
            Scalar(0, 255, 255), 1);

    circle(src, Point(src.cols / 2, src.rows / 2), src.cols / 8, Scalar(255, 255, 0), 2, LINE_AA);

    //填充
    Point pt[1][4];
    pt[0][0] = Point(100, 100);
    pt[0][1] = Point(100, 200);
    pt[0][2] = Point(200, 200);
    pt[0][3] = Point(100, 100);

    const Point *pts[] = {pt[0]};
    int nps[] = {4};
    fillPoly(src, pts, nps, 1, Scalar(255, 0, 0), 8);

    //文字putText LINE_AA抗锯齿
    putText(src, "OpenCV", Point(150, 150), CV_FONT_BLACK, 1, Scalar(255, 255, 0), 1, LINE_AA);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_zeros(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    dest = Mat::zeros(src.size(), src.type());
    int rows = src.rows;
    int cols = (src.cols - 1) * src.channels();
    int channels = src.channels();
    LOGE("bitmap：rows：%d,cols：%d,channels:%d", rows, cols, channels);
    for (int row = 1; row < rows - 1; row++) {
        //获取上一行
        uchar *previous = src.ptr<uchar>(row - 1);
        //获取当前行
        uchar *current = src.ptr<uchar>(row);
        //下一行
        uchar *next = src.ptr<uchar>(row + 1);
        //输出
        uchar *output = dest.ptr<uchar>(row);
        for (int col = channels; col < cols; col++) {
            output[col] = saturate_cast<uchar>(5 * current[col - channels] -
                                               (previous[col] + next[col] +
                                                current[col - channels] + current[col + channels]));
        }
    }
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_blur(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    //均值模糊
    //Size(w,h),只能是基数
    blur(src, dest, Size(15, 15), Point(-1, -1));
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_gaussianBlur(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    //高斯模糊 保留了一些轮廓
    //第四个参数sigmaX
    GaussianBlur(src, dest, Size(15, 15), 0);
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_medianBlur(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    medianBlur(src, dest, 3);
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_medianBlur2(JNIEnv *env, jclass clazz, jobject bitmap) {
    /* Mat src = bitmap2Mat(env, bitmap);
     Mat dest;
     medianBlur(src,dest,7);

     //掩膜
     Mat final;
     Mat kernel;
     kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
     filter2D(dest,final,dest.depth(),kernel);

     mat2bitmap(env, final, bitmap);
     JNU_ThrowByName(env,"java/lang/Exception","medianBlur2 == null");*/

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_bilateralFilter(JNIEnv *env, jclass clazz, jobject bitmap) {
    /* Mat src = bitmap2Mat(env, bitmap);
     Mat dest;
     *//**
     * 主要用来图片美容,基于高斯模糊，高斯模糊保留轮廓并不强,双边保留轮廓信息会增强，基于高斯再增加像素差
     *//*
    bilateralFilter(src,dest,3,1,2);
    mat2bitmap(env, dest, bitmap);
    JNU_ThrowByName(env,"java/lang/Exception","bilateralFilter == null");*/
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_erode(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(src, dest, kernel);
    /*namedWindow("out_image");
    //动态控制
    createTrackbar("Trackbar", "out_image", &element_size, max_size,trackbarCallback);*/
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_dilate(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
    dilate(src, dest, kernel);
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_morphologyEx(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
    /**
        CV_MOP_OPEN 开图像:先腐蚀后膨胀
        CV_MOP_CLOSE 闭图像:先膨胀后腐蚀
        CV_MOP_GRADIENT 梯度:膨胀 - 腐蚀
        CV_MOP_TOPHAT 顶帽:原图像- 开图像【开图像是，先腐蚀后膨胀，所以会得到讲小白色
                            方块去掉的图，之后用原图像去减得到的图像，实际得到的就是小方块图像】
        CV_MOP_BLACKHAT 黑帽：闭图像 - 原图像【闭图像会去先膨胀后腐蚀，就是将原来的图片
                            中的黑点去填充为白色，再减去原图就剩下白色的圆圈】
    */
    morphologyEx(src, dest, CV_MOP_OPEN, kernel);
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_morphologyEx2(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;

    // 方法一、先闭图像后开图像
    Mat final;
    Mat kernel, kernel1;

    kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(src, dest, CV_MOP_CLOSE, kernel);

    kernel1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(dest, final, CV_MOP_OPEN, kernel1);

    mat2bitmap(env, final, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_morphologyEx3(JNIEnv *env, jclass clazz, jobject bitmap) {
    /*Mat src = bitmap2Mat(env, bitmap);
    Mat dest;

    // 方法二、彩色变成黑白再处理
    // 1.变黑白
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 2. 二值化,自动阀值
    Mat binary;
    adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);

    // 3. 开图像
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, dest, CV_MOP_OPEN, kernel);
    // 4. 取反
    bitwise_not(dest,dest);

    mat2bitmap(env, dest, bitmap);*/
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_extractionLine(JNIEnv *env, jclass clazz, jobject bitmap) {
    /*
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;

    // 1.变黑白
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 2. 二值化,自动阀值
    Mat binary;
    adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 0);

    // 3. 开图像 (去除一些乱七八糟的杂点)
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(binary, dest, CV_MOP_OPEN, kernel);

    // 4.中间连接的时候有黑色的小方块，改为白色，膨胀
    kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    dilate(dest, dest, kernel); // 膨胀，取最大
    erode(dest, dest, kernel);// 腐蚀，取最小

    // 5.取水平线
    Mat level = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1));
    erode(dest, dest, level);// 腐蚀，取最小，将不是水平线的变成黑色，
    dilate(dest, dest, level);// 膨胀，取最大，不然线变短了

    *//*
     // 5.取垂直线
    Mat level = getStructuringElement(MORPH_RECT, Size( 1,src.cols/16));
    erode(dest,dest,level);// 腐蚀，取最小，将不是水平线的变成黑色，
    dilate(dest,dest,level);// 膨胀，取最大，不然线变短了
    *//*

    mat2bitmap(env, dest, bitmap);
    */
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_pyrUp(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    // 预计算值
    pyrUp(src, dest, Size(src.cols * 2, src.rows * 2));
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_pyrDown(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    // 1.对图像进行高斯模糊 2.再过滤左右临近点
    pyrDown(src, dest, Size(src.cols / 2, src.rows / 2));
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_filter2D_1robert(JNIEnv *env, jclass clazz,
                                                         jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;

    Mat kernel;
    kernel=(Mat_<int>(2,2)<<1,0,0,-1);
    //depth:值是0-6，type进度的程度
    // 矩阵中元素的一个通道的数据类型，
    // 这个值和type是相关的。例如 type为 CV_16SC2，
    // 一个2通道的16位的有符号整数。那么，depth则是CV_16S。depth也是一系列的预定义值，
    //将type的预定义值去掉通道信息就是depth值:
    //CV_8U用0表示 CV_8S用1表示 CV_16U用2表示 CV_16S用3表示 CV_32S用4表示 CV_32F用5表示 CV_64F用6表示
    filter2D(src,dest,src.depth(),kernel);

    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_filter2D_1soble_1left(JNIEnv *env, jclass clazz,
                                                              jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    //转成灰度图
    Mat gray;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    Mat dest;
    Mat kernel;
    kernel=(Mat_<int>(3,3)<<-1,0,1,-2,0,2,-1,0,1);

    filter2D(gray,dest,src.depth(),kernel);
    mat2bitmap(env, gray, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_filter2D_1soble_1right(JNIEnv *env, jclass clazz,
                                                               jobject bitmap) {
    Mat src = bitmap2Mat(env, bitmap);
    Mat dest;
    Mat kernel;
    kernel=(Mat_<int>(3,3)<<-1,-2,-1,0,0,0,1,2,1);

    filter2D(src,dest,src.depth(),kernel);
    mat2bitmap(env, dest, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencvdemo_NativeUtils_filter2D_1laplace(JNIEnv *env, jclass clazz,
                                                          jobject bitmap) {


}