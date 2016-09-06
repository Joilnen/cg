#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "app_state_and_events.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
void ui(AppStateAndEvents &ae);

#endif
