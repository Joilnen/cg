/***********************
 * Aluno Joilnen Leite
 **********************/

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

#define HM glColor3f(1, 0, 0); \
           glBegin(GL_LINES); \
               glVertex3f(-5, 0, 0); \
               glVertex3f(5, 0, 0); \
               glVertex3f(0, -5, 0); \
               glVertex3f(0, 5, 0); \
           glEnd()
 GLuint m = GL_LINE_LOOP;

#define MAX_NO_TEXTURES 16

using namespace boost::qvm;

int numLines;

typedef enum state {
    waitingforclick,
    clickedonce,
} state;

typedef struct point {
    int x;
    int y;
} point;

point lines[256][2] ;

int gState=waitingforclick;
bool lineisvalid=false;

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
static void drawAircond() {
    extern float col_aircond[3];

    glColor3f(col_aircond[0], col_aircond[1], col_aircond[2]);

    // Aircond
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glTranslatef(300, -100, 0);
    glScalef(0.15, .15, 0.9);

    // face esquerda
    glBegin(m);
        glVertex3f(-50, 100, 0);
        glVertex3f(-50, -100, 0);
        glVertex3f(-50, -100, -25);
        glVertex3f(-50, 100, -25);
    glEnd();

    // face direita
    glBegin(m);
        glVertex3f(50, 100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
    glEnd();

    // face inferior
    glBegin(m);
        glVertex3f(-50, -100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, -100, -25);
        glVertex3f(-50, -100, -25);
    glEnd();

    // face fundo
    glBegin(m);
        glVertex3f(-50, -100, -25);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
        glVertex3f(-50, 100, -25);
    glEnd();

    // face frente
    glBegin(m);
        glVertex3f(-50, -100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, 100, 0);
        glVertex3f(-50, 100, 0);
    glEnd();
    glPopMatrix();
}


static void drawTable() {
    extern float col_table[3];
    extern GLuint texture_id[MAX_NO_TEXTURES];

    glColor3f(col_table[0], col_table[1], col_table[2]);


    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    // Mesa
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glTranslatef(-300, 40, 0);
    glScalef(1, .02, 10.8);

    // face esquerda
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, 100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, -25);
    glEnd();

    // face direita
    glBegin(m);
        glVertex3f(50, 100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
    glEnd();

    // face inferior
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, -100, -25);
    glEnd();

    // face fundo
    glBegin(m);
        glVertex3f(-50, -100, -25);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
        glVertex3f(-50, 100, -25);
    glEnd();

    // face frente
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 100, 0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, 0);
    glEnd();
    glPopMatrix();
}


static void drawBox() {

    extern float col1[3];

    glColor3f(col1[0], col1[1], col1[2]);

    glPushMatrix();

    // face esquerda
    glBegin(m);
        glVertex3f(-400, 200, 0);
        glVertex3f(-400, -200, 0);
        glVertex3f(-400, -200, -400);
        glVertex3f(-400, 200, -400);
    glEnd();
    glPopMatrix();

    // face direita
    glPushMatrix();
    glBegin(m);
        glVertex3f(400, 200, 0);
        glVertex3f(400, -200, 0);
        glVertex3f(400, -200, -400);
        glVertex3f(400, 200, -400);
    glEnd();
    glPopMatrix();

    // face superior
    glPushMatrix();
    glBegin(m);
        glVertex3f(-400, -200, 0);
        glVertex3f(400, -200, 0);
        glVertex3f(400, -200, -400);
        glVertex3f(-400, -200, -400);
    glEnd();
    glPopMatrix();

    // face inferior
    glPushMatrix();
    glBegin(m);
        glVertex3f(-400, 200, 0);
        glVertex3f(400, 200, 0);
        glVertex3f(400, 200, -400);
        glVertex3f(-400, 200, -400);
    glEnd();
    glPopMatrix();

    // face fundo
    glPushMatrix();
    glBegin(m);
        glVertex3f(-400, -200, -400);
        glVertex3f(400, -200, -400);
        glVertex3f(400, 200, -400);
        glVertex3f(-400, 200, -400);
    glEnd();
    glPopMatrix();

    // face frente
    //glPushMatrix();
    //glBegin(m);
    //    glVertex3f(-400, -200, 0);
    //    glVertex3f(400, -200, 0);
    //    glVertex3f(400, 200, 0);
    //    glVertex3f(-400, 200, 0);
    //glEnd();

    glPopMatrix();
}

static void drawDoor() {

    extern float col2[3];

    glColor3f(col2[0], col2[1], col2[2]);

    glPushMatrix();

    glTranslatef(200, 40, 20);
    glScalef(1.4, 1.5, 0.0008);

    extern bool is_door_open;
    if(is_door_open) {
        glTranslatef(-50, 0, 0);
        glRotatef(-90.0, 0.0, 1.0, 0.0);
        glTranslatef(50, 0, 0); 
    }

    // face esquerda
    glBegin(m);
        glVertex3f(-50, 100, 0);
        glVertex3f(-50, -100, 0);
        glVertex3f(-50, -100, -25);
        glVertex3f(-50, 100, -25);
    glEnd();

    // face direita
    glBegin(m);
        glVertex3f(50, 100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
    glEnd();

    // face inferior
    glBegin(m);
        glVertex3f(-50, -100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, -100, -25);
        glVertex3f(-50, -100, -25);
    glEnd();

    // face fundo
    glBegin(m);
        glVertex3f(-50, -100, -25);
        glVertex3f(50, -100, -25);
        glVertex3f(50, 100, -25);
        glVertex3f(-50, 100, -25);
    glEnd();

    // face frente
    glBegin(m);
        glVertex3f(-50, -100, 0);
        glVertex3f(50, -100, 0);
        glVertex3f(50, 100, 0);
        glVertex3f(-50, 100, 0);
    glEnd();

    glPopMatrix();
}

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(512, 512,  300, 300, 10, 10);
    glViewport(0, 0, windowwidth, windowheight);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);

    glEnable(GL_CULL_FACE);

    glEnable(GL_NORMALIZE);
    glEnable(GL_POINT_SMOOTH);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
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

    glMatrixMode(GL_MODELVIEW);


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


