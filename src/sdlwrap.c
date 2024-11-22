#include "sdlwrap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_video.h>

SDL_Window* g_sdlwindow;
SDL_GLContext g_context;

void init_sdl_video(const char* title, int wid, int hei) {
    g_sdlwindow = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        wid == 0 ? 1280 : wid, 
        hei == 0 ? 960 : hei, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    g_context = SDL_GL_CreateContext(g_sdlwindow);
}

void deinit_sdl_video() {
    SDL_GL_DeleteContext(g_context);
    SDL_DestroyWindow(g_sdlwindow);
    g_sdlwindow = NULL;
}

uint32_t do_sdl_event_updates() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            return -1;
    }

    return 0;
}
