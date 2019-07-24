#include <SDL.h>
#include <SDL_main.h>
#include <android/log.h>
#include <unistd.h>
#include <jni.h>

//SDL_Window *window;
//SDL_Renderer *renderer;

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "ERRROR");
//      exit(1);
    }

    __android_log_print(ANDROID_LOG_ERROR, "HQM", "OK");
    int c = 0;

    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    jclass clazz = (*env)->GetObjectClass(env, activity);

    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 0");
    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 1");
    jmethodID methodID = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 2");
    jobject a =(*env)->NewObject(env,cls, methodID, 5);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 3");


    jclass hqsdk = (*env)->FindClass(env, "io/humanteq/hqsdk_core_legacy/HQSdk");
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 6");
    jmethodID hqsdkInit = (*env)->GetStaticMethodID(env, hqsdk, "init", "(Landroid/content/Context;Ljava/lang/String;)V");
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 7");
    jstring *key = (*env)->NewStringUTF(env, "38e44d7");
    (*env)->CallStaticVoidMethod(env, hqsdk, hqsdkInit, activity, key);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 8");


    (*env)->DeleteLocalRef(env, activity);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 4");
    (*env)->DeleteLocalRef(env, clazz);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 5");
    // find the identifier of the method to call
//    jmethodID method_id = env->GetMethodID(clazz, "showHome", "()V");
//
//    // effectively call the Java method
//    env->CallVoidMethod(activity, method_id);
//
//    // clean up the local references.


    while(1) {
        sleep(1);
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "%d", c++);
    }
    return 0;
 }
