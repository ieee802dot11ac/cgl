#pragma once
#include <SDL2/SDL.h>
#include <stdint.h>

extern SDL_Window* g_sdlwindow;
extern SDL_GLContext g_context;

void init_sdl_video(const char* title, int wid, int hei);

void deinit_sdl_video();

uint32_t do_sdl_event_updates();
