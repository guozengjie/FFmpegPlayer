#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include <pthread.h>
#include "VideoChannel.h"
#include "AudioChannel.h"

extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;
#define loge(...) __android_log_print(ANDROID_LOG_ERROR, "FFmpeg", __VA_ARGS__)
pthread_t pid;
VideoChannel *videoChannel;
AudioChannel *audioChannel;

void *task_open_input(void *void_url) {
//    防止url指向的地址内存释放
    const char *url = static_cast<const char *>(void_url);
    char *dataSource = new char[strlen(url)];
    strcpy(dataSource, url);
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
        //1.根据编码方式得到解码器
        AVCodec *codec = avcodec_find_decoder(avCodecParameters->codec_id);
        if (codec == nullptr) {
            loge("获取解码器失败");
        } else {
            loge("解码器为：%s", codec->name);
        }
        //2.编码器上下文
        AVCodecContext *context = avcodec_alloc_context3(codec);
        //3.打开解码器
        if (avcodec_open2(context, codec, nullptr) < 0) {
            loge("打开解码器失败");
        }
        if (avCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            loge("视频流");
            videoChannel = new VideoChannel;
        } else if (avCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioChannel = new AudioChannel;
            loge("音频流");
        }
    }

    finish:
    delete dataSource;
    if (videoChannel != nullptr)
        delete videoChannel;
    if (audioChannel != nullptr)
        delete audioChannel;
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