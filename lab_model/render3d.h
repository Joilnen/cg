#ifndef RENDER_3D
#define RENDER_3D
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "app_state_and_events.h"

void init_render();
void render(SDL_Window *, AppStateAndEvents &);

#endif


