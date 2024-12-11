#pragma once

#include <SDL2/SDL_opengl.h>
#include <stdlib.h>

typedef struct _tex {
    uint tex_id;
    uint tex_name; // refers to GL_TEXTURE# macros 
} texture_t;

texture_t* new_texture(uint len, GLenum format, GLenum type, const void* img);

texture_t* new_texture_ext(uint len, GLenum internal_fmt, GLenum format, GLenum type, const void* img);

void activate_texture(texture_t* tex);
