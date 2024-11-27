#include "tex.h"
#include <stdlib.h>

GL_Texture* new_texture(uint len, GLenum format, GLenum type, const void *img) {
    return new_texture_ext(len, format, format, type, img);    
}

GL_Texture* new_texture_ext(uint len, GLenum internal_fmt, GLenum format, GLenum type, const void* img) {
    static uint tex_name_idx;
    GL_Texture* ret_tex = malloc(sizeof(GL_Texture));

    glActiveTexture(GL_TEXTURE0 + ++tex_name_idx);
    ret_tex->tex_name = GL_TEXTURE0 + tex_name_idx;

    glGenTextures(1, &ret_tex->tex_id);
    glBindTexture( GL_TEXTURE_2D, ret_tex->tex_id);

    // here lies TMU config hell. there is no honor to be gained here.
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    // glEnable(GL_TEXTURE_GEN_R);
    // glEnable(GL_TEXTURE_GEN_Q);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    // glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    // glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format, len, len, 0, format, type, img);

    return ret_tex;
}

void activate_texture(GL_Texture* tex) {
    glActiveTexture(tex->tex_name);
    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    glEnable(GL_TEXTURE_2D);
}
