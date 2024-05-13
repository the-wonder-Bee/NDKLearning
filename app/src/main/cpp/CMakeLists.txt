# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

# 指定cmake的最小版本 NDK版本和Android Gradle插件版本兼容的CMake版本， 只影响项目构建和编译过程，不影响运行时
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_ANDROID_ARCH_ABI armeabi-v7a)
# Declares and names the project. 声明项目名称

project("myapplication")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/liaofeng)

#添加一个第三方库， 当开发需要生成一个新的so库的时候
add_library( # Sets the name of the library.
             native-lib
#             SHARED
        STATIC
        #指定native-lib库的源文件,不需要加头文件,源文件可以写多个
             native-lib.cpp
             test.cpp
        )




#在ndk中查找log库, 并将它的路径保存到${log-lib}中
#第一个参数是: log库的路径
#第二个参数是: log库的名称
find_library(log-lib log)

find_library(libtest1 native-lib)
message(STATUS "This is a simple message: ${libtest1}")

#将目标库native-lib链接到log库中, 这样native-lib库就能调用log库的功能,
#第一个参数是: 目标库
#第二个参数是: 目标库需要依赖的库,依赖库里面有目标库所需要的功能和模块
target_link_libraries(native-lib ${log-lib} )