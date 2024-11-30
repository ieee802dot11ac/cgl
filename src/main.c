#include <SDL2/SDL.h>
#include "mesh.h"
#include "sdlwrap.h"
#include "video.h"

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	init_sdl_video("test", WIDTH, HEIGHT);
	init_ogl(WIDTH, HEIGHT);
	init_mesh();
	mesh_t* mesh = new_mesh(3, 1, SDL_TRUE);
	mesh->verts[0].pos = (vector3_t){1,1,-1}; mesh->verts[0].color = (vector3_t){1,1,1};
	mesh->verts[1].pos = (vector3_t){0,1,-1}; mesh->verts[1].color = (vector3_t){1,1,1};
	mesh->verts[2].pos = (vector3_t){1,0,-1}; mesh->verts[2].color = (vector3_t){1,1,1};
	mesh->faces->idx0 = 0; mesh->faces->idx1 = 1; mesh->faces->idx2 = 2;
	while (1) {
		if (do_sdl_event_updates() != 0) break;
		do_ogl_updates();
    	SDL_GL_SwapWindow(g_sdlwindow);
	}

	delete_mesh(mesh, SDL_TRUE);
	deinit_sdl_video();
	SDL_Quit();
	return 0;
}
