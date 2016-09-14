#include <GL/gl.h>
#include <GL/glu.h>
#include "door.h"
#include "cube.h"

void drawDoor_() {

    extern float col2[3];
    extern GLuint m;

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glColor3f(col2[0], col2[1], col2[2]);
    glColor3f(1, 1, 1);

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
        glTexCoord2f(0, 0); glVertex3f(-50, -100, -25);
        glTexCoord2f(1, 0); glVertex3f(50, -100, -25);
        glTexCoord2f(1, 1); glVertex3f(50, 100, -25);
        glTexCoord2f(0, 1); glVertex3f(-50, 100, -25);
    glEnd();

    // face frente
    glBegin(m);
        glTexCoord2f(1, 0); glVertex3f(-50, -100, 0);
        glTexCoord2f(0, 0); glVertex3f(50, -100, 0);
        glTexCoord2f(0, 1); glVertex3f(50, 100, 0);
        glTexCoord2f(1, 1); glVertex3f(-50, 100, 0);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawDoor() {
    extern bool is_door_open;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        if(is_door_open) {
            glTranslatef(-0.8, -0.17, -20);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            glTranslatef(-140, 0.17, -36);
        }
        glScalef(55, 150, 5);
        glTranslatef(0.8, 0.17, 20);
        drawCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


