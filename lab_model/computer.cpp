#include <GL/gl.h>
#include <GL/glu.h>

void drawComputer() {
    extern GLuint m;
    extern float col_computer[3];

    glColor3f(col_computer[0], col_computer[1], col_computer[2]);

    //// Teclado
    glPushMatrix();

    glTranslatef(60, 35, 0);
    glRotatef(180, 0, 1, 0);

    glRotatef(10, 0, 0, 1);
    glScalef(.2, .002, 0.8);

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


    // Cpu
    glPushMatrix();

    glTranslatef(50, 30, 0);
    glRotatef(180, 0, 1, 0);

    glTranslatef(0, 0, 0);
    glTranslatef(-30, 0, 0);
    glScalef(.3, .04, 0.8);

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

    // Monitor
    glPushMatrix();

    glTranslatef(50, 30, 0);
    glRotatef(180, 0, 1, 0);

    glTranslatef(0, 0, 0);
    glTranslatef(-30, -20, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(.3, .008, 0.8);

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


