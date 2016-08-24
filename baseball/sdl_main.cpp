#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include <stdio.h>
#include <math.h>
// #include "untitled.h"
#include "render2d.h"
#include "event.h"
#include "ui.h"
#include "app_state_and_events.h"

#include <iostream>
#include <array>

using namespace std;

int windowwidth;
int windowheight;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int ac, char *av[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    SDL_Window *window = SDL_CreateWindow("ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    if(glcontext == NULL) {
        cout << "No context \n";
        exit(-1);
    }
    else {
        glewExperimental = GL_TRUE; 
        GLenum glewError = glewInit();
        if( glewError != GLEW_OK ) {
            cout << "Error initializing GLEW " <<  glewGetErrorString( glewError);
            exit(-1);
        }
    }

    ImGui_ImplSdl_Init(window);

    ImVec4 clear_color = ImColor(114, 144, 154, 0);

    glEnable(GL_DEPTH_TEST); // Depth Testing
    // glEnable(GL_PROGRAM_POINT_SIZE); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float rotateCube = 0; // Apply rotation on cube
    init_render2d();
    AppStateAndEvents ae;
    std::array<GLfloat, 3> v({0, 6, 4});
    ae.setCameraPos(v);
    // Main loop
    bool done = false;
    for (;!done;) {

        ImGui_ImplSdl_NewFrame(window);
        done = event(ae);
        ui(ae);
        render2d(window, ae);

        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        ImGui::Render();
        glPopAttrib();
        glPopMatrix();

        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

