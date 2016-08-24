/***********************
 * Aluno Joilnen Leite
 **********************/

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <sys/time.h>
#include "render2d.h"
#include "imgui.h"

#include "palace.h"
#include "func.h"
#include "app_state_and_events.h"

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
bool pause = true;

bool by_eq = false;
bool draw_chairs = false;
float grossa = 1.0;
// bool is_drawlines = false;
#define INPUT KeyPressMask | ExposureMask 

SDL_Window *lpwin = NULL;

void mouseclick(int button, int state,int x, int y) {

    if(button==BUTTON_RIGHT && state==BUTTON_UP) {
        switch(gState) {
            case waitingforclick:
                ++numLines;
                lines[numLines][0].x=x;
                lines[numLines][0].y=y;
                lines[numLines][1].x=x;
                lines[numLines][1].y=y;
                gState++;
            break;
            case clickedonce:
                lines[numLines][1].x=x;
                lines[numLines][1].y=y;
                gState=waitingforclick;
            break;
        }
    }
}

void mousedrag(int x, int y) {
    if(gState==clickedonce) {
        lines[numLines][1].x=x;
        lines[numLines][1].y=y;
    }
}

void draw_by_circle_equation(int x0, int y0, int radius, int q) {
  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;

  while( y <= x ) {
    if(q == 1 || q == 5) {
        glVertex2i( x + x0,  y + y0); // Octant 1
        glVertex2i( y + x0,  x + y0); // Octant 2
    }

    if(q == 1 || q == 5) {
        glVertex2i(-y + x0,  x + y0); // Octant 3
        // glVertex2i(-x + x0,  y + y0); // Octant 4
    }

    if(q == 3 || q == 5) {
        glVertex2i(-x + x0, -y + y0); // Octant 5
        glVertex2i(-y + x0, -x + y0); // Octant 6
    }

    if(q == 1 || q == 5) {
        glVertex2i( x + x0, -y + y0); // Octant 7
        // glVertex2i( y + x0, -x + y0); // Octant 8
    }

    y++;

    if (decisionOver2<=0)
      decisionOver2 += 2 * y + 1;
    else {
      x--;
      decisionOver2 += 2 * (y - x) + 1;
    }
  }
}

void draw_by_line_equation(int x1, int y1, int x2, int y2) {

    int x = x1, y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    float step, xinc, yinc, v;

    if(dx > dy)
        step = abs(dx);
    else
        step = abs(dy);
    xinc = dx / (float) step;
    yinc = dy / (float) step;

    for(v = 0; v < step; v++) {
        x = x + xinc;
        y = y + yinc;
        glVertex2i(x, y);
    }
}

void draw_by_circle_bresenham(int xm, int ym, int r, int q) {

   int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */ 

   do {
      if(q == 1 || q == 5) glVertex2i(xm - x, ym + y);
      if(q == 2 || q == 5) glVertex2i(xm - y, ym - x);
      if(q == 3 || q == 5) glVertex2i(xm + x, ym - y);
      if(q == 4 || q == 5) glVertex2i(xm + y, ym + x);
      r = err;

      if (r <= y) err += ++y * 2 + 1;           /* e_xy + e_y < 0 */

      if (r > x || err > y) err += ++x * 2 + 1; /* e_xy + e_x > 0 or no 2nd y - step */

   } while (x < 0);
}

void draw_by_line_bresenham(int x0, int y0, int x1, int y1) {

   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */

   for(;;){  /* loop */
      // setPixel(x0,y0);
      glVertex2i(x0, y0);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

extern float col1[3], col2[3], col3[3];

static void draw_by_line_circle_eq() {

    glColor3f(col1[0], col1[1], col1[2]);
    draw_by_line_equation(-200, -250, -200, 200);
    draw_by_line_equation(-200, -250, 300, -400);

    // horizontais
    draw_by_line_equation(-190, -240, -190, -120);
    draw_by_line_equation(-70, -240, -70, -120);

    draw_by_line_equation(-190, -120, -70, -120);
    draw_by_line_equation(-190, -240, -70, -240);

    glColor3f(col2[0], col2[1], col2[2]);
    draw_by_circle_equation(-95, -145, 150, 1);
    draw_by_circle_equation(-25, -75, 250, 1);
}

static void draw_by_bresenham_eq() {
    glColor3f(0, 1, 0);

    // draw_by_circle_equation(0, -250, 200, 1);
    glColor3f(col1[0], col1[1], col1[2]);
    draw_by_line_bresenham(-200, -250, -200, 200);
    draw_by_line_bresenham(-200, -250, 300, -250);

    // horizontais
    draw_by_line_bresenham(-190, -240, -190, -120);
    draw_by_line_bresenham(-70, -240, -70, -120);

    draw_by_line_bresenham(-190, -120, -70, -120);
    draw_by_line_bresenham(-190, -240, -70, -240);

    glColor3f(col2[0], col2[1], col2[2]);
    draw_by_circle_equation(-95, -145, 150, 1);
    draw_by_circle_equation(-25, -75, 250, 1);
}

static void DrawBaseBallField(AppStateAndEvents &ae, float dT) {
    static float angle = 180.0f;
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 512,
              0, 0, 0,
              0, 1, 0);

    glPointSize(grossa);
    glBegin(GL_POINTS);
        if(by_eq)
            draw_by_line_circle_eq();
        else
            draw_by_bresenham_eq();
    glEnd();
}

void drawlines() {

    glColor3f(col3[0], col3[1], col3[2]);
    glBegin(GL_POINTS);
    for(int i=0; i<=numLines; i++) {
        // glVertex2i(lines[i][0].x, gHeight-lines[i][0].y);
        // glVertex2i(lines[i][1].x, gHeight-lines[i][1].y);
        if(by_eq)
            draw_by_line_equation(lines[i][0].x - 500 ,300-lines[i][0].y,
                            lines[i][1].x - 500, 300-lines[i][1].y);
        else
            draw_by_line_bresenham(lines[i][0].x - 500 ,300-lines[i][0].y,
                            lines[i][1].x - 500, 300-lines[i][1].y);
        // draw_by_line_bresenham(lines[i][0].x ,300-lines[i][0].y,
        //                lines[i][1].x, 300-lines[i][1].y);
    }
    glEnd();
}


void SetUpOpenGL() {
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
    glColor4f(1, 1, 1, 1);
}

float GetTimeInterval() {
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

void Resize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float) width / (float) height, 0.15, 251.0);
    glViewport(0, 0, width, height);
}

void init_render2d() {
    SetUpOpenGL();
    GetTimeInterval();
}

float t, T = 0.0;
void render2d(SDL_Window *win, AppStateAndEvents &ae) {
    // Rendering
    lpwin = win;
    ImVec4 clear_color = ImColor(114, 144, 154, 0);
    GLint display_w, display_h;
    SDL_GetWindowSize(win, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (double)display_w / (double)display_h, 0.1, 3000);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // DrawScene(ae, t);
    DrawBaseBallField(ae, t);
    drawlines();
}


