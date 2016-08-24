#ifndef RENDER_2D
#define RENDER_2D
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "app_state_and_events.h"

void init_render2d();
void render2d(SDL_Window *, AppStateAndEvents &);
void mousedrag(int, int);
void mouseclick(int , int ,int, int);

#define BUTTON_RIGHT 1
#define BUTTON_UP 1


#endif


