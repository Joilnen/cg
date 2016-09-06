#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "event.h"
#include "app_state_and_events.h"
#include "render2d.h"

#include <iostream>

using namespace std;

bool event(AppStateAndEvents &ae) {
    SDL_Event &event = ae.getEvent();
    static GLfloat phi = 0.1, theta = 0.3;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSdl_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            return true;
        else if (event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE)
                return true;
            if (event.key.keysym.sym == SDLK_w) {
                std::array<GLfloat, 3> v = ae.getCameraPos();
                v[2] -= ae.getStep();
                ae.setCameraPos(v);
            }
            if (event.key.keysym.sym == SDLK_s) {
                std::array<GLfloat, 3> v = ae.getCameraPos();
                v[2] += ae.getStep();
                ae.setCameraPos(v);
            }
            if (event.key.keysym.sym == SDLK_a) {
                std::array<GLfloat, 3> v = ae.getCameraPos();
                v[1] -= ae.getStep();
                ae.setCameraPos(v);
            }
            if (event.key.keysym.sym == SDLK_d) {
                std::array<GLfloat, 3> v = ae.getCameraPos();
                v[1] += ae.getStep();
                ae.setCameraPos(v);
            }

            if (event.key.keysym.sym == SDLK_c) {
                SDL_SetRelativeMouseMode(static_cast<SDL_bool>(!SDL_GetRelativeMouseMode()));
                ae.setMouseToCamera(!ae.getMouseToCamera());
            }

        }

        if(ae.getMouseToCamera() && event.type == SDL_MOUSEWHEEL) {
            std::array<GLfloat, 3> v = ae.getCameraPos();
            v[1] += (event.wheel.y * ae.getStep());
            ae.setCameraPos(v);
        }
    }

    return false;
}

