#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

const uint8_t test_texture[48] = {
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
	0x3F,0x3F,0x3F,
	0xFF,0xFF,0xFF,
};

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* w = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext(w);

    glViewport(0, 0, 1280, 960);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    const float DEG2RAD = SDL_acos(-1.0f) / 180;
	const float front = 0.1;
	const float back = 1000;

	float tangent = SDL_tan(100.0/2 * DEG2RAD);	// tangent of half fovY
	float top = front * tangent;				// half height of near plane
	float right = top * (1280/960);				// half width of near plane

    float mtx[16] = {0};
    mtx[0] = front/right;
	mtx[5] = front/top;
	mtx[9] = -(back + front) / (back - front);
	mtx[10] = -1;
	mtx[14] = -(2 * back * front) / (back - front);
	mtx[15] =  0;

    glMatrixMode(GL_PROJECTION);
    glFrustum(-right, right, -top, top, front, back);

    unsigned int tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, test_texture);

    SDL_Event event;
    while (1) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return -1;
            default:;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(1,0.85); glVertex3f(-0.5,0.5,-1);
        glTexCoord2f(1,0); glVertex3f(-0.5,-0.5,-1);
        glTexCoord2f(0,1); glVertex3f(0.5,0.5,-1);
        glTexCoord2f(0,0.15); glVertex3f(0.5,-0.5,-1);
        glEnd();

        uint err = glGetError();
        if (err != GL_NO_ERROR) {
            dprintf(2, "oh shit! gl errored with 0x%X! that's bad!\n", err);
            exit(-1);
        }
    	SDL_GL_SwapWindow(w);
    }
}
