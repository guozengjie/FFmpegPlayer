#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include <pthread.h>


extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;

pthread_t pid;

void *run(void *) {
    __android_log_print(ANDROID_LOG_ERROR, "TAG", "新建线程，打开直播源");
    //  打开视频输入流
    AVFormatContext *ps;
    int res = avformat_open_input(&ps, "http://cbnlive.cbchot.com/live/yt_chc_h_1.m3u8?123",
                                  nullptr, nullptr);
    __android_log_print(ANDROID_LOG_ERROR, "TAG", "打开直播源return:%d", res);
    pthread_exit(&pid);
}

extern "C"
JNIEXPORT void JNICALL
Java_club_guozengjie_cplusplus_FFmpegPlayer_jniPrepare(JNIEnv *env, jobject thiz, jstring jurl) {
//    新建线程
    const char *url = env->GetStringUTFChars(jurl, nullptr);
    pthread_create(&pid, nullptr, run, nullptr);
    env->ReleaseStringUTFChars(jurl, url);
}