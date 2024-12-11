#include <SDL2/SDL.h>
#include "mesh.h"
#include "sdlwrap.h"
#include "tex.h"
#include "video.h"

#define WIDTH 1280
#define HEIGHT 960

const uint8_t test_texture[48] = {
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
	0,0,0,
	0xFF,0xFF,0xFF,
};

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	init_sdl_video("test", WIDTH, HEIGHT);
	init_ogl(WIDTH, HEIGHT);
	init_mesh();
	mesh_t* mesh = new_mesh(4, 2, SDL_TRUE);
	mesh->verts[0].pos = (vector3_t){1,1,-1}; mesh->verts[0].color = (vector3_t){1,1,1}; mesh->verts[0].uv = (vector2_t){1,0};
	mesh->verts[1].pos = (vector3_t){0,1,-1}; mesh->verts[1].color = (vector3_t){1,1,1}; mesh->verts[1].uv = (vector2_t){1,0};
	mesh->verts[2].pos = (vector3_t){1,0,-1}; mesh->verts[2].color = (vector3_t){1,1,1}; mesh->verts[2].uv = (vector2_t){1,0};
	mesh->verts[3].pos = (vector3_t){0,0,-1}; mesh->verts[3].color = (vector3_t){1,0,1}; mesh->verts[3].uv = (vector2_t){1,0};
	mesh->faces[0].idx0 = 0; mesh->faces[0].idx1 = 1; mesh->faces[0].idx2 = 2; 
	mesh->faces[1].idx0 = 1; mesh->faces[1].idx1 = 3; mesh->faces[1].idx2 = 2;
	//mesh->texture = new_texture(4, GL_RGB, GL_UNSIGNED_BYTE, test_texture);
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
