#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>


extern "C" {
#include <libavutil/avutil.h>
}
using namespace std;

extern "C"
JNIEXPORT void JNICALL
Java_club_guozengjie_cplusplus_FFmpegPlayer_jniPrepare(JNIEnv *env, jobject thiz, jstring url) {

}