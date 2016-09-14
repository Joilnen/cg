/***********************
 * Aluno: Joilnen Leite
 ***********************/

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <sys/time.h>
#include "renderLab.h"
#include "imgui.h"
#include "computer.h"

#include "app_state_and_events.h"
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/quat.hpp>
#include <boost/qvm/quat_operations.hpp>

#include <Magick++.h>

#include <iostream>
#include <array>
#include "load_tex.h"

#include "door.h"
#include "table.h"
#include "box.h"
#include "aircond.h"
#include "press.h"

#define HM glColor3f(1, 0, 0); \
           glBegin(GL_LINES); \
               glVertex3f(-5, 0, 0); \
               glVertex3f(5, 0, 0); \
               glVertex3f(0, -5, 0); \
               glVertex3f(0, 5, 0); \
           glEnd()
// GLuint m = GL_LINE_LOOP;
GLuint m = GL_LINE_LOOP;

#define MAX_NO_TEXTURES 16

using namespace boost::qvm;
using namespace std;
using namespace Magick;

float rotateSpeed = 180.0f; /* degrees per second */

// bool is_drawlines = false;
#define INPUT KeyPressMask | ExposureMask 

static SDL_Window *lpwin = NULL;

/****
math::Vec3f windowToObjectf(const math::Vec3f& windowCoord) {
  math::Matrix4f modelViewMatrix;
  math::Matrix4f projectionMatrix;
  std::array <GLint, 4> viewport;
  glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix.data() );
  glGetFloatv( GL_PROJECTION_MATRIX, projectionMatrix.data() );
  glGetIntegerv( GL_VIEWPORT, &viewport.front() );
  math::Vec3f ret(0, 0, 0);
  auto succes = gluUnProject( windowCoord.x , windowCoord.y, windowCoord.z, modelViewMatrix.data(), projectionMatrix.data(), &viewport.front(), &ret.x, &ret.y, &ret.z );
  RASSERT(succes == GL_TRUE);
  GL_RASSERT();
  return ret;
}
****/

static void drawScene(AppStateAndEvents &ae, float dT) {
    static float angle = 180.0f;
    // glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt(0, 512, 512,
    //           0, 0, 0,
    //           0, 1, 0);
    gluLookAt(
        ae.getCameraPos()[0], ae.getCameraPos()[1], ae.getCameraPos()[2],
        ae.getCameraTarget()[0], ae.getCameraTarget()[1], ae.getCameraTarget()[2],
        0, 0, 1
    );

    // glLoadIdentity();
    HM;
    drawBox();
    drawDoor();
    drawComputer();
    drawTable();
    drawAircond();
    drawPress();

    if(ae.isWire())
        m = GL_LINE_LOOP;
    else
        m = GL_QUADS;
}

void setUpOpenGL() {
    int windowwidth, windowheight;
    if(lpwin)
        SDL_GetWindowSize(lpwin, &windowwidth, &windowheight);
    else
        windowwidth = 1024; windowheight = 600;
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat ambient_light[] = {.2, .2, .2, 1.0};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(512, 512,  300, 300, 10, 10);
    glViewport(0, 0, windowwidth, windowheight);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    loadTex();
}

float getTimeInterval() {
    static struct timeval time = {0, 0};
    static struct timeval last = {0, 0};
    int sec, usec;

    gettimeofday(&time, NULL);

    sec = time.tv_sec - last.tv_sec;
    usec = time.tv_usec - last.tv_usec;

    last.tv_sec = time.tv_sec;
    last.tv_usec = time.tv_usec;

    sec *= 1000000;
    sec += usec;

    return (float) sec / 1.0e6;
}

void init_renderLab() {
    setUpOpenGL();
    getTimeInterval();
}

float t, T = 0.0;
void renderLab(SDL_Window *win, AppStateAndEvents &ae) {
    // Rendering
    lpwin = win;
    ImVec4 clear_color = ImColor(114, 144, 154, 0);
    GLint display_w, display_h;
    SDL_GetWindowSize(win, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (double)display_w / (double)display_h, 0.1, 3000);
    // glOrtho(-display_w / 2, display_w / 2,  -display_h / 2, display_h / 2, 800, -800);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawScene(ae, t);
}


