#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include <pthread.h>


extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, "FFmpeg", __VA_ARGS__)
pthread_t pid;

void *task_open_input(void *url) {
//    防止url指向的地址内存释放
    char *dataSource = new char[256];
    strcpy(dataSource, static_cast<const char *>(url));
    loge("直播源地址%s", dataSource);
    //  打开视频输入流
    AVFormatContext *ps;
    int res = avformat_open_input(&ps, dataSource,
                                  nullptr, nullptr);
    if (res == 0) {
        loge("打开直播源成功");
    } else {
        loge("打开直播源失败");
    }
    pthread_exit(&pid);
}

extern "C"
JNIEXPORT void JNICALL
Java_club_guozengjie_cplusplus_FFmpegPlayer_jniPrepare(JNIEnv *env, jobject thiz, jstring jurl) {
//    新建线程
    const char *url = env->GetStringUTFChars(jurl, nullptr);
    pthread_create(&pid, nullptr, task_open_input,
                   (void *) url);
    env->ReleaseStringUTFChars(jurl, url);
}