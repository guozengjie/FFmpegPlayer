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
    AVFormatContext *ps = nullptr;
    int res = avformat_open_input(&ps, dataSource,
                                  nullptr, nullptr);
    if (res == 0) {
        loge("打开直播源成功");
    } else {
        loge("打开直播源失败");
    }
    if (ps == nullptr) {
        goto finish;
    }
    for (int i = 0; i < ps->nb_streams; i++) {
        AVStream *avStream = ps->streams[i];
        AVCodecParameters *avCodecParameters = avStream->codecpar;
        //根据编码方式得到解码器
        AVCodec *avCodec = avcodec_find_decoder(avCodecParameters->codec_id);
        if (avCodec == nullptr) {
            loge("获取解码器失败");
        } else {
            loge("解码器为：%s", avCodec->name);
        }
    }
    finish:
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