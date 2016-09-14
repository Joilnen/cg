#include <GL/gl.h>
#include <GL/glu.h>

void drawCube() {

    // White side - BACK
    glBegin(GL_POLYGON);
        glColor3f(   1.0,  1.0, 1.0 );
        glTexCoord2f(0, 0); glVertex3f(  0.5, -0.5, 0.5 );
        glTexCoord2f(0, 1); glVertex3f(  0.5,  0.5, 0.5 );
        glTexCoord2f(1, 1); glVertex3f( -0.5,  0.5, 0.5 );
        glTexCoord2f(1, 0); glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    //  // Purple side - RIGHT
    glBegin(GL_POLYGON);
        glColor3f(  1.0,  0.0,  1.0 );
        glTexCoord2f(0, 0);  glVertex3f( 0.5, -0.5, -0.5 );
        glTexCoord2f(0, 1);  glVertex3f( 0.5,  0.5, -0.5 );
        glTexCoord2f(1, 1);  glVertex3f( 0.5,  0.5,  0.5 );
        glTexCoord2f(1, 0);  glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
        glColor3f(   0.0,  1.0,  0.0 );
        glTexCoord2f(0, 0); glVertex3f( -0.5, -0.5,  0.5 );
        glTexCoord2f(0, 1); glVertex3f( -0.5,  0.5,  0.5 );
        glTexCoord2f(1, 1); glVertex3f( -0.5,  0.5, -0.5 );
        glTexCoord2f(1, 0); glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
        glColor3f(  0.0,  0.0,  1.0);
        glTexCoord2f(0, 0); glVertex3f( 0.5,  0.5,  0.5);
        glTexCoord2f(0, 1); glVertex3f( 0.5,  0.5, -0.5);
        glTexCoord2f(1, 1); glVertex3f(-0.5,  0.5, -0.5);
        glTexCoord2f(1, 0); glVertex3f(-0.5,  0.5,  0.5);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
        glColor3f(   1.0,  0.0,  0.0 );
        glTexCoord2f(0, 0); glVertex3f(  0.5, -0.5, -0.5 );
        glTexCoord2f(0, 1); glVertex3f(  0.5, -0.5,  0.5 );
        glTexCoord2f(1, 1); glVertex3f( -0.5, -0.5,  0.5 );
        glTexCoord2f(1, 0); glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
}


