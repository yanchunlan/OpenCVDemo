//
// Created by ycl on 2020/1/10.
//
#pragma once
#ifndef OPENCVDEMO_ANDROIDLOG_H
#define OPENCVDEMO_ANDROIDLOG_H

#include <android/log.h>

#define LOG_DEBUG  true

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"native",FORMAT,##__VA_ARGS__);
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"native",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"native",FORMAT,##__VA_ARGS__);



#endif //OPENCVDEMO_ANDROIDLOG_H
