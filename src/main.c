#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdlwrap.h"
#include "video.h"

#define WIDTH 1280
#define HEIGHT 960

int main(int argc, char** argv) {
		printf("h-hewwo~\n");
		SDL_Init(SDL_INIT_EVERYTHING);
		init_sdl_video("test", WIDTH, HEIGHT);
		init_ogl(WIDTH, HEIGHT);
		while (1) {
			if (do_sdl_event_updates() != 0) break;
			do_ogl_updates();
    		SDL_GL_SwapWindow(g_sdlwindow);
		}

		deinit_sdl_video();
		SDL_Quit();
		return 0;
}
