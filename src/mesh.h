#pragma once
#include <SDL2/SDL_stdinc.h>

typedef struct _vec3 {
    float x,y,z;
} vector3_t;

typedef struct _vtx {
    vector3_t pos;
    vector3_t color;
} vertex_t;

typedef struct _face {
    uint16_t idx0, idx1, idx2;
} face_t;

typedef struct _mesh {
    vertex_t* verts;
    face_t* faces;
    uint16_t vert_ct;
    uint16_t face_ct;
} mesh_t;

extern mesh_t** rendering_mesh_stack;
extern uint32_t render_stack_size;

void init_mesh();

mesh_t* new_mesh(uint16_t vert_ct, uint16_t face_ct, SDL_bool add_to_stack);

void do_mesh_stack_updates();

void delete_mesh(mesh_t* mesh, SDL_bool remove_from_stack);
