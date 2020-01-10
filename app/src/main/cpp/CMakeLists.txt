cmake_minimum_required(VERSION 3.4.1)

include_directories(include)

# 编译jni文件
file(GLOB my_source_path ${CMAKE_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/*.c)
add_library(OpenCV SHARED ${my_source_path})

# 绑定 so 位置
add_library(lib_opencv SHARED IMPORTED)
set_target_properties(lib_opencv
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_java4.so)


find_library( log-lib
              log )

# <android/bitmap.h>
find_library(jnigraphics-lib
        jnigraphics)

target_link_libraries( OpenCV
        ${log-lib}
        ${jnigraphics-lib}
        lib_opencv)

# 未知的需要添加 add_library，系统中有的需要查找 find_library，外部的需要设置位置 set_target_properties