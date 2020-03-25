#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>


extern "C" {
#include <libavutil/avutil.h>
}
#define TAG "JNI_LOG"
#define LOG(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
using namespace std;

extern "C"
JNIEXPORT void JNICALL
Java_club_guozengjie_cplusplus_FFmpegPlayer_jniPrepare(JNIEnv *env, jobject thiz, jstring url) {
    // TODO: implement jni_prepare()
}