#include "video.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int do_wireframe;
uint8_t image[64] = { 0xAF };
uint tex_id = 0;

void init_ogl(int wid, int hei) {

    glViewport(0, 0, wid, hei);
    glClearColor(0.0, 0.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_FLAT);

    const float DEG2RAD = SDL_acos(-1.0f) / 180;
	const float front = 0.1;
	const float back = 1000;
	
	float tangent = SDL_tan(100.0/2 * DEG2RAD);	// tangent of half fovY
	float top = front * tangent;				// half height of near plane
	float right = top * (wid/hei);				// half width of near plane

    float mtx[16] = {0};
    mtx[0] = front/right;
	mtx[5] = front/top;
	mtx[9] = -(back + front) / (back - front);
	mtx[10] = -1;
	mtx[14] = -(2 * back * front) / (back - front);
	mtx[15] =  0;

    glMatrixMode(GL_PROJECTION);
    glFrustum(-right, right, -top, top, front, back);

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &tex_id);
    glBindTexture( GL_TEXTURE_2D, tex_id);

    // here lies TMU config hell. there is no honor to be gained here.
    glEnable(GL_TEXTURE_2D);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 8, 8, 0, GL_RED, GL_UNSIGNED_BYTE, image);

    glFinish();
}

void do_ogl_updates(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glActiveTexture(GL_TEXTURE0);
    glBegin(do_wireframe ? GL_LINE_LOOP : GL_TRIANGLE_STRIP);

    glColor3f(0,0,0); glTexCoord2f(-0.66, 0); glVertex3f(-0.66, 0.66,-1);
    glColor3f(0,0,0); glTexCoord2f(5, 0); glVertex3f(-0.66, -0.66,-1);
    glColor3f(0,0,0); glTexCoord2f(0, 5); glVertex3f(0.66, 0.66,-1);
    glColor3f(0,1,0); glTexCoord2f(0, 0); glVertex3f(0.66, -0.66,-1);
    
    glEnd();

    glFinish();
    
    uint err = glGetError();
    if (err != GL_NO_ERROR) {
        dprintf(2, "oh shit! gl errored with %i! that's bad!\n", err);
        exit(-1);
    }
}

