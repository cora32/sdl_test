#include <SDL.h>
#include <SDL_main.h>
#include <android/log.h>
#include <unistd.h>
#include <jni.h>
#include "hqm.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_bool done = SDL_FALSE;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        __android_log_print(ANDROID_LOG_ERROR, "HQM", "ERR");
        exit(1);
    }

    // init
    hqm_init(
            "38e44d7", // sdk key
            1,         // enable debug mode
            1);        // allow background tasks

    // collect apps
    hqm_collect_apps();

    // log events
    hqm_log("test", "just a string");
    hqm_log("test", "{\"text\": \"sdl_test\", \"event\": \"app_start\"}");

    // get user groups
    UserGroupData hqm_group_data = hqm_get_user_groups();
    if(hqm_group_data.userGroups != NULL)
        for (int i = 0; i < hqm_group_data.length; i++, hqm_group_data.userGroups++) {
            __android_log_print(ANDROID_LOG_ERROR,
                                "HQM", "id:\"%s\" name:\"%s\"",
                                hqm_group_data.userGroups->id,
                                hqm_group_data.userGroups->name);
        }

//    SDL_Window *window;
//    SDL_Renderer* renderer;
//    window = SDL_CreateWindow(
//            "An SDL2 window",                  // window title
//            SDL_WINDOWPOS_UNDEFINED,           // initial x position
//            SDL_WINDOWPOS_UNDEFINED,           // initial y position
//            640,                               // width, in pixels
//            480,                               // height, in pixels
//            SDL_WINDOW_OPENGL                  // flags - see below
//    );
//    renderer = SDL_CreateRenderer(window, -1, 0);
//    SDL_Color textColor = { 255, 255, 255, 0 };
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "test text", textColor);
//    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
//    int text_width = textSurface->w;
//    int text_height = textSurface->h;
//    SDL_FreeSurface(textSurface);
//    SDL_Rect renderQuad = { 20, 1080 - 30, text_width, text_height };
//    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
//    SDL_DestroyTexture(text);

    int c = 0;
    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
//            __android_log_print(ANDROID_LOG_ERROR, "HQM", "event.type: %x", event.type);
            switch (event.type) {
                case SDL_AUDIODEVICEADDED:
                    __android_log_print(ANDROID_LOG_ERROR, "HQM", "SDL_DISPLAYEVENT: %d", c++);

//                    Redraw();
                    break;
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_TRUE;
                    break;

            }
        }
    }

    SDL_Quit();

    return 0;
}
