#include <SDL.h>
#include <SDL_main.h>
#include <android/log.h>
#include <unistd.h>
#include <jni.h>
#include "hqm.c"

//SDL_Window *window;
//SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "ERRROR");
        exit(1);
    }

    __android_log_print(ANDROID_LOG_ERROR, "HQM", "OK");
    int c = 0;

    // init
    hqm_init("38e44d7", 1);

    // collect apps
    hqm_collect_apps();

    // log events
    hqm_log("test", "just a string");
    hqm_log("test", "{\"text\": \"sdl_test\", \"event\": \"app_start\"}");

    // get user groups
    UserGroupData *hqm_group_data = hqm_get_user_groups();
    for (int i = 0; i < hqm_group_data->length; ++i, hqm_group_data->userGroups++) {
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "%s %s", hqm_group_data->userGroups->id,
                            hqm_group_data->userGroups->name);
    }
//    for (int i = 0; i < hqm_group_data->length; ++i, hqm_group_data->userGroups++)
//        free(hqm_group_data->userGroups);
    free(hqm_group_data);


    while (1) {
        sleep(1);
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "%d", c++);
    }
    return 0;
}
