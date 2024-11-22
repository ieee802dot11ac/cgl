#include "video.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void init_ogl(int wid, int hei) {
    glViewport(0, 0, wid, hei);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_DEPTH_TEST);

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
}

void do_ogl_updates(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0, 0.3,-3);
    glColor3f(0, 1.0, 0);
    glVertex3f(-0.33, -0.3,-3);
    glColor3f(0, 0, 1.0);
    glVertex3f(0.33, -0.3,-3);
    glEnd();
    
}

