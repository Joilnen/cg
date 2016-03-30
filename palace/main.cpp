#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


int main()
{
    int b_run = 1;
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erro\n");
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window *w = SDL_CreateWindow("Palace", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(w);

    while(b_run) {
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_QUIT)
                b_run = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}


