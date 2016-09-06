#ifndef RENDER_LAB
#define RENDER_LAB

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "app_state_and_events.h"

void setUpOpenGL();
void init_renderLab();
void renderLab(SDL_Window *, AppStateAndEvents &);
void mousedrag(int, int);
void mouseclick(int , int ,int, int);

#define BUTTON_RIGHT 1
#define BUTTON_UP 1


#endif


