#include "mesh.h"
#include "tex.h"
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>

mesh_t** rendering_mesh_stack = NULL;
uint32_t render_stack_size = 0;

void init_mesh() { rendering_mesh_stack = malloc(0); }

mesh_t* new_mesh(uint16_t vert_ct, uint16_t face_ct, SDL_bool add_to_stack) {
    mesh_t* mesh = SDL_malloc(sizeof(mesh_t));
    mesh->verts = SDL_malloc(vert_ct * sizeof(vertex_t));
    mesh->vert_ct = vert_ct;
    mesh->faces = SDL_malloc(face_ct * sizeof(face_t));
    mesh->face_ct = face_ct;
    if (add_to_stack) {
        rendering_mesh_stack = SDL_realloc(rendering_mesh_stack, ++render_stack_size * sizeof(void*));
        rendering_mesh_stack[render_stack_size - 1] = mesh;
    }

    return mesh;
}

void do_mesh_stack_updates() {
    for (int i = 0; i < render_stack_size; i++) {
        mesh_t* working = rendering_mesh_stack[i];
        if (working->texture) {
            activate_texture(working->texture);
        }
        glBegin(GL_TRIANGLES);
        if (working->texture) {
            for (int j = 0; j < working->face_ct; j++) {
                vertex_t vtx = working->verts[working->faces[i].idx0];
                glTexCoord2f(vtx.uv.x, vtx.uv.y);
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
                vtx = working->verts[working->faces[i].idx1];
                glTexCoord2f(vtx.uv.x, vtx.uv.y);
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
                vtx = working->verts[working->faces[i].idx2];
                glTexCoord2f(vtx.uv.x, vtx.uv.y);
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
            }
        } else {
            for (int j = 0; j < working->face_ct; j++) {
                vertex_t vtx = working->verts[working->faces[i].idx0];
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
                vtx = working->verts[working->faces[i].idx1];
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
                vtx = working->verts[working->faces[i].idx2];
                glColor3f(vtx.color.x, vtx.color.y, vtx.color.z);
                glVertex3f(vtx.pos.x, vtx.pos.y, vtx.pos.z);
            }
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}

void delete_mesh(mesh_t* mesh, SDL_bool remove_from_stack) {
    SDL_free(mesh->verts);
    SDL_free(mesh->faces);
    SDL_free(mesh);

    if (remove_from_stack) {
        mesh_t** saved_mesh_stack_ptr = rendering_mesh_stack;
        mesh_t** new_mesh_stack = SDL_malloc((render_stack_size - 1) * sizeof(void*));
        for (int i = 0; i < render_stack_size; i++) {
            if (rendering_mesh_stack[i] == mesh) {
                rendering_mesh_stack++;
                if (i >= render_stack_size - 1) break;
            }
            new_mesh_stack[i] = rendering_mesh_stack[i];
        }
        render_stack_size--;
        SDL_free(saved_mesh_stack_ptr);
        rendering_mesh_stack = new_mesh_stack;
    }
}
