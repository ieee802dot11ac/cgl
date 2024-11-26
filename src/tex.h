#pragma once

#include <SDL2/SDL_opengl.h>
#include <stdlib.h>

typedef struct _gl_tex {
    uint tex_id;
    uint tex_name; // refers to GL_TEXTURE# macros 
} GL_Texture;

GL_Texture* new_texture(uint len, GLenum format, GLenum type, const void* img);

void activate_texture(GL_Texture* tex);
