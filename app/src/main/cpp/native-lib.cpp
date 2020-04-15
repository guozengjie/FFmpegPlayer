#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>


extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;

extern "C"
JNIEXPORT void JNICALL
Java_club_guozengjie_cplusplus_FFmpegPlayer_jniPrepare(JNIEnv *env, jobject thiz, jstring jurl) {
    AVFormatContext *ps;
    const char * url=env->GetStringUTFChars(jurl, nullptr);
    avformat_open_input(&ps,url,nullptr, nullptr);
    env->ReleaseStringUTFChars(jurl, url);
//    __android_log_print(ANDROID_LOG_ERROR, "FFMPEG", "AAAAAAAAAAAA");
}