#include <GL/gl.h>
#include <GL/glu.h>
#include "door.h"
#include "cube.h"
#include "load_tex.h"

extern GLuint  texture_id[TEX_NUMBER];
void drawQuad() {
    extern bool is_door_open;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[WALL_OUT]);
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


