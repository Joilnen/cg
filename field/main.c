#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define WIDTH  800
#define HEIGHT 460

unsigned short borl = 1;
float grossa = 1.0;


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
int gHeight;
float color_1[3] = {0,1,0};

void init(void) {
    glClearColor(0x05/255.0, 0x56/255.0, 0x1B/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
    numLines=-1;
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

void draw_by_line_equation(int x1, int y1, int x2, int y2) {
// (y1 - y2)x + (x2 - x1)y = (x2y1 - x1y2)
    int x = x1, y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int step, xinc, yinc, v;
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

void draw_by_circle_equation(int x0, int y0, int radius, int q) {
  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;

  while( y <= x ) {
    if(q == 1 || q == 5) {
        glVertex2i( x + x0,  y + y0); // Octant 1
        glVertex2i( y + x0,  x + y0); // Octant 2
    }

    if(q == 2 || q == 5) {
        glVertex2i(-y + x0,  x + y0); // Octant 3
        glVertex2i(-x + x0,  y + y0); // Octant 4
    }

    if(q == 3 || q == 5) {
        glVertex2i(-x + x0, -y + y0); // Octant 5
        glVertex2i(-y + x0, -x + y0); // Octant 6
    }

    if(q == 4 || q == 5) {
        glVertex2i( x + x0, -y + y0); // Octant 7
        glVertex2i( y + x0, -x + y0); // Octant 8
    }

    /****
    if(q == 1 || q == 5) glVertex2i(-x + x0, -y + y0); // Octant 5
    if(q == 2 || q == 5) glVertex2i(-y + x0, -x + y0); // Octant 6
    if(q == 3 || q == 5) glVertex2i( x + x0, -y + y0); // Octant 7
    if(q == 4 || q == 5) glVertex2i( y + x0, -x + y0); // Octant 8
    ****/
    y++;

    if (decisionOver2<=0)
      decisionOver2 += 2 * y + 1;
    else {
      x--;
      decisionOver2 += 2 * (y - x) + 1;
    }
  }
}

void draw_field_bresenham() {

    unsigned short corner_1x = 30, corner_1y = 50;
    unsigned short corner_2x = WIDTH - 30, corner_2y = 50;
    unsigned short corner_3x = WIDTH - 30, corner_3y = HEIGHT - 50;
    unsigned short corner_4x = 30, corner_4y = HEIGHT - 50;
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    // big quad bresenham
    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_bresenham(corner_1x, corner_1y, corner_2x, corner_2y);
        draw_by_line_bresenham(corner_2x, corner_2y, corner_3x, corner_3y);
        draw_by_line_bresenham(corner_3x, corner_3y, corner_4x, corner_4y);
        draw_by_line_bresenham(corner_4x, corner_4y, corner_1x, corner_1y);
    glEnd();

    // middle circle bresenham
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_bresenham(WIDTH / 2, HEIGHT / 2, 100, 5);
        draw_by_circle_bresenham(WIDTH / 2, HEIGHT / 2, 10, 5);
    glEnd();

    // corners circles
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_bresenham(corner_1x, corner_1y, 15, 1);
        draw_by_circle_bresenham(corner_2x, corner_2y, 15, 2);
        draw_by_circle_bresenham(corner_3x, corner_3y, 15, 3);
        draw_by_circle_bresenham(corner_4x, corner_4y, 15, 4);
    glEnd();

    // small quads and small circles
    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_bresenham(corner_1x, corner_1y + HEIGHT / 4, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_line_bresenham(corner_1x, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /2);
        draw_by_line_bresenham(corner_1x + 80, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_circle_bresenham(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 1);
        draw_by_circle_bresenham(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 4);

        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4, corner_1x + WIDTH - 60, corner_1y + HEIGHT /4);
        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 60, corner_1y + HEIGHT /2);
        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4);
        draw_by_circle_bresenham(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 4 + corner_1y + HEIGHT / 2)/ 2, 30, 2);
        draw_by_circle_bresenham(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/ 2, 30, 3);
    glEnd();

    // middle
    corner_1x += WIDTH / 2 - 30;
    glBegin(GL_POINTS);
        draw_by_line_bresenham(corner_1x, corner_1y, corner_1x, corner_1y + HEIGHT - 100);
    glEnd();
}

void draw_field_line() {

    unsigned short corner_1x = 30, corner_1y = 50;
    unsigned short corner_2x = WIDTH - 30, corner_2y = 50;
    unsigned short corner_3x = WIDTH - 30, corner_3y = HEIGHT - 50;
    unsigned short corner_4x = 30, corner_4y = HEIGHT - 50;
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5, 0.5, 1.0);

    // big quad bresenham
    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_bresenham(corner_1x, corner_1y, corner_2x, corner_2y);
        draw_by_line_bresenham(corner_2x, corner_2y, corner_3x, corner_3y);
        draw_by_line_bresenham(corner_3x, corner_3y, corner_4x, corner_4y);
        draw_by_line_bresenham(corner_4x, corner_4y, corner_1x, corner_1y);
    glEnd();

    // middle circle bresenham
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_equation(WIDTH / 2, HEIGHT / 2, 100, 5);
        draw_by_circle_equation(WIDTH / 2, HEIGHT / 2, 10, 5);
    glEnd();

    // corners circles
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_equation(corner_1x, corner_1y, 15, 1);
        draw_by_circle_equation(corner_2x, corner_2y, 15, 2);
        draw_by_circle_equation(corner_3x, corner_3y, 15, 3);
        draw_by_circle_equation(corner_4x, corner_4y, 15, 4);
    glEnd();

    // small quads and small circles
    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_bresenham(corner_1x, corner_1y + HEIGHT / 4, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_line_bresenham(corner_1x, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /2);
        draw_by_line_bresenham(corner_1x + 80, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_circle_equation(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 1);
        draw_by_circle_equation(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 4);

        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4, corner_1x + WIDTH - 60, corner_1y + HEIGHT /4);
        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 60, corner_1y + HEIGHT /2);
        draw_by_line_bresenham(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4);
        draw_by_circle_equation(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 4 + corner_1y + HEIGHT / 2)/ 2, 30, 2);
        draw_by_circle_equation(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/ 2, 30, 3);
    glEnd();

    // middle
    corner_1x += WIDTH / 2 - 30;
    glBegin(GL_POINTS);
        draw_by_line_bresenham(corner_1x, corner_1y, corner_1x, corner_1y + HEIGHT - 100);
    glEnd();
}

void draw_field_line_() {
    unsigned short corner_1x = 30, corner_1y = 50;
    unsigned short corner_2x = WIDTH - 30, corner_2y = 50;
    unsigned short corner_3x = WIDTH - 30, corner_3y = HEIGHT - 50;
    unsigned short corner_4x = 30, corner_4y = HEIGHT - 50;
    unsigned short count = 0;
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_equation(corner_1x, corner_1y, corner_2x, corner_2y);
        draw_by_line_equation(corner_2x, corner_2y, corner_3x, corner_3y);
        draw_by_line_equation(corner_3x, corner_3y, corner_4x, corner_4y);
        draw_by_line_equation(corner_4x, corner_4y, corner_1x, corner_1y);
    glEnd();

    // middle circle bresenham
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_equation(WIDTH / 2, HEIGHT / 2, 100, 5);
        draw_by_circle_equation(WIDTH / 2, HEIGHT / 2, 10, 5);
    glEnd();

    // corners circles
    glBegin(GL_POINTS);
        glVertex2i(WIDTH / 2, HEIGHT / 2);
        draw_by_circle_equation(corner_1x, corner_1y, 15, 1);
        draw_by_circle_equation(corner_2x, corner_2y, 15, 2);
        draw_by_circle_equation(corner_3x, corner_3y, 15, 3);
        draw_by_circle_equation(corner_4x, corner_4y, 15, 4);
    glEnd();

    // small quads and small circles
    glBegin(GL_POINTS);
        glVertex2i(corner_1x, corner_1y);
        glVertex2i(corner_2x, corner_2y);
        glVertex2i(corner_3x, corner_3y);
        glVertex2i(corner_4x, corner_4y);
        draw_by_line_equation(corner_1x, corner_1y + HEIGHT / 4, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_line_equation(corner_1x, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /2);
        draw_by_line_equation(corner_1x + 80, corner_1y + HEIGHT / 2, corner_1x + 80, corner_1y + HEIGHT /4);
        draw_by_circle_equation(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 1);
        draw_by_circle_equation(corner_1x + 80, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/2, 30, 4);

        draw_by_line_equation(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4, corner_1x + WIDTH - 60, corner_1y + HEIGHT /4);
        draw_by_line_equation(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 60, corner_1y + HEIGHT /2);
        draw_by_line_equation(corner_1x + WIDTH - 140, corner_1y + HEIGHT / 2, corner_1x + WIDTH - 140, corner_1y + HEIGHT / 4);
        draw_by_circle_equation(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 4 + corner_1y + HEIGHT / 2)/ 2, 30, 2);
        draw_by_circle_equation(corner_1x + WIDTH - 140, (corner_1y + HEIGHT / 2 + corner_1y + HEIGHT / 4)/ 2, 30, 3);
    glEnd();

    // middle
    corner_1x += WIDTH / 2 - 30;
    glBegin(GL_POINTS);
        draw_by_line_equation(corner_1x, corner_1y, corner_1x, corner_1y + HEIGHT - 100);
    glEnd();
}

void draw_field() {
    if(borl == 1)
        draw_field_line();
    else if(borl == 2)
        draw_field_bresenham();
}

void keyboard(unsigned char k, int x, int y) {
    if(k == 27)
        exit(0);
}

void drawlines() {
    glColor3fv(color_1);
    // glBegin(GL_LINES);
    // for(int i=0; i<=numLines; i++) {
    //     glVertex2i(lines[i][0].x, gHeight-lines[i][0].y);
    //     glVertex2i(lines[i][1].x, gHeight-lines[i][1].y);
    // }
    // glEnd();

    glBegin(GL_POINTS);
    for(int i=0; i<=numLines; i++) {
        // glVertex2i(lines[i][0].x, gHeight-lines[i][0].y);
        // glVertex2i(lines[i][1].x, gHeight-lines[i][1].y);
        if(borl == 1)
            draw_by_line_equation(lines[i][0].x ,gHeight-lines[i][0].y,
                            lines[i][1].x, gHeight-lines[i][1].y);
        else if(borl == 2)
            draw_by_line_bresenham(lines[i][0].x ,gHeight-lines[i][0].y,
                            lines[i][1].x, gHeight-lines[i][1].y);
    }
    glEnd();
}


void display() {
    glClearColor(0x05/255.0, 0x56/255.0, 0x1B/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_field();
    glLineWidth(grossa);
    drawlines();
    glLineWidth(1.f);
    glutSwapBuffers();
}

void process_event(int option) {
    if(option == 3) {
        if(grossa == 1.0)
            grossa = 5.0;
        else
            grossa = 1.0;
    }
    else
        borl = option;
    printf("%f\n", grossa);
    glutPostRedisplay();
}

void create_menu() {

    int menu = glutCreateMenu(process_event); 
    glutAddMenuEntry("Eq. reta", 1);
    glutAddMenuEntry("Bresenham", 2);
    glutAddMenuEntry("Linha +/- grossa", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseclick(int button, int state,int x, int y) {

    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
        switch(gState) {
            case waitingforclick:
                printf("one clidk");
                ++numLines;
                lines[numLines][0].x=x;
                lines[numLines][0].y=y;
                lines[numLines][1].x=x;
                lines[numLines][1].y=y;
                gState++;
            break;
            case clickedonce:
                printf("2 clidk");
                lines[numLines][1].x=x;
                lines[numLines][1].y=y;
                gState=waitingforclick;
            break;
        }
    }
    glutPostRedisplay();
}

void mousedrag(int x, int y) {
    if(gState==clickedonce) {
        lines[numLines][1].x=x;
        lines[numLines][1].y=y;
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    gHeight=height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0,height);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Trabalho de CG: Joilnen");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, WIDTH, HEIGHT);
    init();

    create_menu();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMouseFunc(mouseclick);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mousedrag);
    glutMainLoop();

    return 0;
}


