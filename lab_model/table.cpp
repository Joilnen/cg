#include <GL/gl.h>
#include <GL/glu.h>
#include "table.h" 

void drawTable() {
    extern float col_table[3];
    extern GLuint m;
    extern GLuint texture_id;

    glColor3f(col_table[0], col_table[1], col_table[2]);

    // Mesa
    glPushMatrix();

    glTranslatef(80, 40, 40);
    glScalef(0.5, .02, 6.8);

    // face esquerda
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, 100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, -25);
    glEnd();

    // face direita
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(50, 100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(50, 100, -25);
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
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -100, -25);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, -25);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, -25);
    glEnd();

    // face frente
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 100, 0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, 0);
    glEnd();
    glPopMatrix();


    glPushMatrix();

    glTranslatef(80, 40, -90);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, .02, 6.8);

    // face esquerda
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, 100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, -25);
    glEnd();

    // face direita
    glBegin(m);
        glTexCoord2f(0.0, 0.0); glVertex3f(50, 100, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, 0);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, -100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(50, 100, -25);
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
        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -100, -25);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, -100, -25);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 100, -25);
        glTexCoord2f(0.0, 1.0); glVertex3f(-50, 100, -25);
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


