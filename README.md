# OpenCVDemo

OpenCV的demo

### plugin
- AndroidStudio : 3.5.2
- Gradle : 5.4.1
- OpenCV 4.1.0

### 配置OpenCv环境
1. [下载android版本OpenCV](https://github.com/opencv/opencv/releases)

2. 复制 opencv-4.1.0-android-sdk.zip\OpenCV-android-sdk\sdk\native\jni
   中的include到cpp<br> 复制
   opencv-4.1.0-android-sdk.zip\OpenCV-android-sdk\sdk\native\libs
   中相应的so复制到jniLibs里面

3. 配置cmake环境支持OpenCV

### 原理
    
    工具类：
        bitmap2Mat: Bitmap -> Pixel -> DesMat 
        mat2Bitmap: Bitmap -> Pixel -> DesMat ; srcMat -> desMat
    常规处理流程：
        输入 -> bitmap -> mat -> 针对mat对rgba进行操作 -> bitmap -> 输出
        
    
    
### 笔记
1. 滤镜
2. Mat对象与图像混合
3. 图像的绘制与卷积
4. 图片美容
5. 验证码识别
6. 自定义线性滤波
