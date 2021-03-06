#include <GL/gl.h>
#include <GL/glu.h>
#include "box.h"
#include "cube.h"
#include "load_tex.h"

extern GLuint  texture_id[TEX_NUMBER];

void drawBox() {
    extern float col1[3];
    extern GLuint m;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[DOOR]);
    glColor3f(col1[0], col1[1], col1[2]);

    // Esquerda
    glPushMatrix();
        glScalef(33, 150, 5);
        glTranslatef(2.5, 0.17, 20);
        drawCube();
    glPopMatrix();

    // Canto superior esquerdo
    glPushMatrix();
        glScalef(33, 49.5, 5);
        glTranslatef(2.5, -1.5, 20);
        drawCube();
    glPopMatrix();

    // Em cima da porta
    glPushMatrix();
        glScalef(52, 49.5, 5);
        glTranslatef(.85, -1.5, 20);
        drawCube();
    glPopMatrix();

    // Direita
    glPushMatrix();
        glScalef(117.5, 150, 5);
        glTranslatef(-0.35, 0.17, 20);
        drawCube();
    glPopMatrix();

    // Canto superior direito
    glPushMatrix();
        glScalef(117.5, 150, 5);
        glTranslatef(-0.35, -0.17, 20);
        drawCube();
    glPopMatrix();

    // Resto do lab
    glPushMatrix();
        glScalef(200, 200, 5);
        glTranslatef(0, 0, -20);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glScalef(5, 200, 200);
        glTranslatef(-20, 0, 0);
        drawCube();
    glPopMatrix();

    glPushMatrix();
        glScalef(5, 200, 200);
        glTranslatef(20, 0, 0);
        drawCube();
    glPopMatrix();

    // Chao
    glPushMatrix();
        glTranslatef(0, 100, 0);
        glScalef(200, 5, 200);
        drawCube();
    glPopMatrix();

    // Teto
    glPushMatrix();
        glTranslatef(0, -100, 0);
        glScalef(200, 5, 200);
        drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


