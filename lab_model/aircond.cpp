#include <GL/gl.h>
#include <GL/glu.h>
#include "aircond.h"

void drawAircond() {
    extern float col_aircond[3];
    extern GLuint m;

    glColor3f(col_aircond[0], col_aircond[1], col_aircond[2]);

    // Aircond
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glTranslatef(-88, -70, 0);
    glScalef(0.15, .1, 0.9);

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


