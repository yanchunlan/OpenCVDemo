//
// Created by ycl on 2020/1/13.
//

#ifndef OPENCVDEMO_UTILS_H
#define OPENCVDEMO_UTILS_H


#include <jni.h>
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include "AndroidLog.h"


using namespace cv;

extern "C" {
    Mat bitmap2Mat(JNIEnv *env, jobject bitmap);

    void mat2bitmap(JNIEnv *env, Mat src, jobject bitmap);
}


#endif //OPENCVDEMO_UTILS_H
