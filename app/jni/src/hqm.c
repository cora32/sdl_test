#include <SDL.h>
#include <SDL_main.h>
#include <android/log.h>
#include <unistd.h>
#include <jni.h>

typedef struct _UserGroup {
    char id[32];
    char name[32];
} UserGroup;

typedef struct _UserGroupData {
    UserGroup *userGroups;
    int length;
} UserGroupData;

void hqm_init(char *key_string, int enable_debug) {
    JNIEnv *env = (JNIEnv *) SDL_AndroidGetJNIEnv();
    jobject activity = (jobject) SDL_AndroidGetActivity();
    jclass activity_class = (*env)->GetObjectClass(env, activity);

    jclass hqsdk_class = (*env)->FindClass(env, "io/humanteq/hqsdk_core_legacy/HQSdk");

    // enabling debug
    jmethodID hqsdk_enable_debug = (*env)->GetStaticMethodID(env, hqsdk_class, "enableDebug",
                                                             "(Z)V");
    (*env)->CallStaticVoidMethod(env, hqsdk_class, hqsdk_enable_debug,
                                 (jboolean) (enable_debug == JNI_TRUE));

    // initing sdk
    jmethodID sdk_init_method = (*env)->GetStaticMethodID(env, hqsdk_class, "init",
                                                          "(Landroid/content/Context;Ljava/lang/String;)V");
    (*env)->CallStaticVoidMethod(env, hqsdk_class, sdk_init_method, activity,
                                 (*env)->NewStringUTF(env, key_string));

    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, activity_class);
    (*env)->DeleteLocalRef(env, hqsdk_class);
}

void hqm_collect_apps() {
    JNIEnv *env = (JNIEnv *) SDL_AndroidGetJNIEnv();
    jobject activity = (jobject) SDL_AndroidGetActivity();
    jclass activity_class = (*env)->GetObjectClass(env, activity);

    jclass hqsdk_class = (*env)->FindClass(env, "io/humanteq/hqsdk_core_legacy/HQSdk");

    // collect apps
    jmethodID collect_apps_method = (*env)->GetStaticMethodID(env, hqsdk_class, "collectApps",
                                                              "(Landroid/content/Context;)V");
    (*env)->CallStaticVoidMethod(env, hqsdk_class, collect_apps_method, activity);

    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, activity_class);
    (*env)->DeleteLocalRef(env, hqsdk_class);
}

void hqm_log(char *event_name, char *event_data) {
    JNIEnv *env = (JNIEnv *) SDL_AndroidGetJNIEnv();

    jclass hqsdk_class = (*env)->FindClass(env, "io/humanteq/hqsdk_core_legacy/HQSdk");

    // log event
    jmethodID log_event_method = (*env)->GetStaticMethodID(env, hqsdk_class, "logEvent",
                                                           "(Ljava/lang/String;Ljava/lang/String;)V");
    (*env)->CallStaticVoidMethod(env, hqsdk_class, log_event_method,
                                 (*env)->NewStringUTF(env, event_name),
                                 (*env)->NewStringUTF(env, event_data));

    (*env)->DeleteLocalRef(env, hqsdk_class);
}

UserGroupData *hqm_get_user_groups() {
    JNIEnv *env = (JNIEnv *) SDL_AndroidGetJNIEnv();

    jclass hqsdk_class = (*env)->FindClass(env, "io/humanteq/hqsdk_core_legacy/HQSdk");

    // get user groups
    jmethodID user_groups_method = (*env)->GetStaticMethodID(env, hqsdk_class,
                                                           "getUserGroupsSync",
                                                           "()Ljava/util/List;");
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 11");
    jarray groups = (*env)->CallStaticObjectMethod(env, hqsdk_class, user_groups_method);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "-- 12");

    char *name = "test_name\0";
    char *id = "test_id\0";
    char *name2 = "test_name 2\0";
    char *id2 = "test_id 2\0";

    UserGroup *userGroups = malloc(10 * sizeof(UserGroup));

    strncpy(userGroups[0].name, name, strlen(name));
    strncpy(userGroups[0].id, id, strlen(id));
    strncpy(userGroups[1].name, name2, strlen(name2));
    strncpy(userGroups[1].id, id2, strlen(id2));
    strncpy(userGroups[2].name, name2, strlen(name2));
    strncpy(userGroups[2].id, id2, strlen(id2));

    (*env)->DeleteLocalRef(env, hqsdk_class);
    __android_log_print(ANDROID_LOG_ERROR, "HQM", "hqm_collect_apps cleared hqsdk_class");

    UserGroupData *userGroupData = malloc(sizeof(UserGroupData));
    userGroupData->userGroups = userGroups;
    userGroupData->length = 10;

    return userGroupData;
}