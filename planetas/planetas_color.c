/*** Aluno Joilnen Leite ***/

#include <GL/glut.h>
#include <stdlib.h>

static int year = 0, day = 0;
#define BUFSIZE 512

#define TORUS		1
#define TETRAHEDRON	2
#define ICOSAHEDRON	3

GLuint selectBuf[BUFSIZE];
void init() {
  GLfloat light_ambient[] =
  {0.2, 0.2, 0.2, 1.0};
  GLfloat light_diffuse[] =
  {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] =
  {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position1[] =
  {1.0, 1.0, 0.0, 0.0};
  GLfloat light_position2[] =
  {0.0, -2.0, -2.0, 0.0};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
  // glEnable(GL_LIGHT1);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
}

void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 0.0);

    glTranslatef (0.0, 0.0, 0.0); //Translada a partir do novo sistema de coordenadas resultante da Rotacao
	glPushMatrix();
		glRotatef ((GLfloat) year, 1.0, 0.0, 0.0);
		glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
		glutSolidSphere(1.0, 20, 16);   /* desenha o sol */
	glPopMatrix();

	glColor3f (0.6, 0.4, 0.4);
    glPushMatrix();
        glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
        glTranslatef (2.0, 0.0, 0.0); //Translada a partir do novo sistema de coordenadas resultante da Rotacao
        glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
        glutSolidSphere(0.1, 16, 16);    /* desenha um planeta */
    glPopMatrix();

	glColor3f (0.4, 0.6, 0.4);
	glPushMatrix();
		glRotatef (-(GLfloat) year, 0.0, 1.0, 0.0);
		glTranslatef (2.2, 0.0, 0.0); //Translada a partir do novo sistema de coordenadas resultante da Rotacao
		glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
		glutSolidSphere(0.15, 15, 16);    /* desenha um planeta */

	    glColor3f (0.8, 0.6, 0.3);
        glPushMatrix();
            glRotatef ((GLfloat) year * 4, 0.0, 0.0, 1.0);
            glTranslatef (0.0, 0.3, 0.0); //Translada a partir do novo sistema de coordenadas resultante da Rotacao
            glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
            glutSolidSphere(0.05, 10, 10);    /* desenha um planeta */
        glPopMatrix();

	    glColor3f (0.8, 0.2, 0.2);
		glRotatef (-(GLfloat) year * 4, 0.0, 1.0, 1.0);
		glTranslatef (0.3, 0.3, 0.0); //Translada a partir do novo sistema de coordenadas resultante da Rotacao
		glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
		glutSolidSphere(0.05, 10, 10);    /* desenha um planeta */

	glPopMatrix();

	glutSwapBuffers(); //pois estamos adotando o GLUT_DOUBLE

}

void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //posicao da camera

}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
        case 'd':
            day = (day + 10) % 360;  //% valor do resto
            glutPostRedisplay(); //Redesenha a cena com novas coordenadas, é executado no glutMainLoop;
            break;
        case 'D':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Rotacao de Planetas");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


