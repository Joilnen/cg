#include <GL/glut.h>
#include <stdlib.h>

/**
 *  Mapa de bits ou bitmap utilizado como padrao pra preenchimento
 *  aqui o padrao eh em 32 bits, 4 x byte
 */
GLubyte tux[] = {
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x7f,  0xfe,  0x0, 
     0x0,  0xc4,  0x23,  0x0, 
     0x1,  0x83,  0x21,  0x80, 
     0x1,  0x7,  0xe0,  0x80, 
     0x1,  0x7,  0xf0,  0x80, 
     0x1,  0x8f,  0xf9,  0x80, 
     0x0,  0xff,  0xff,  0x0, 
     0x0,  0x4f,  0xf1,  0x0, 
     0x0,  0x6f,  0xf1,  0x0, 
     0x0,  0x2f,  0xf3,  0x0, 
     0x0,  0x27,  0xe2,  0x0, 
     0x0,  0x30,  0x66,  0x0, 
     0x0,  0x1b,  0x1c,  0x0, 
     0x0,  0xb,  0x88,  0x0, 
     0x0,  0xb,  0x98,  0x0, 
     0x0,  0x8,  0x18,  0x0, 
     0x0,  0xa,  0x90,  0x0, 
     0x0,  0x8,  0x10,  0x0, 
     0x0,  0xc,  0x30,  0x0, 
     0x0,  0x6,  0x60,  0x0, 
     0x0,  0x3,  0xc0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0, 
     0x0,  0x0,  0x0,  0x0
};

GLfloat r,g,b;

/** Funcao inicial seta o estado inicial da FSM GL */
void init(void);
/** Funcao de desenho */
void display(void);

void keyboard(unsigned char key, int x, int y);

void mouse(int button, int state, int x, int y);

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Preenchendo regiões");
  init();
  glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

/** Funcao inicial seta o estado inicial da FSM GL */
void init(void){
    /** Seta cor para 'limpar' a tela, com opacidade ma'xima */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    /** Seta a visao da camera para cena cono ortogonal, o tamanho do objeto nao sofre influencia 
     * para a distancia da camera */.
    glOrtho (0, 256, 0, 256, -1 ,1);

    r=0; g=1; b=0;
}

/** Funcao de desenho */
void display(void){
    int i;
    /** Seta o bit para usar o buffer de cores */
    glClear(GL_COLOR_BUFFER_BIT);
    /** Desabilita o uso de preenchimento na construccao dos poligonos */
    glDisable(GL_POLYGON_STIPPLE);

    /** Seta o estilo de desenho dos poligonos, neste caso
     * desenha os lados como linhas e as faces de tras */
    glPolygonMode(GL_BACK, GL_LINE);
    /** Seta cor vermelha */
    glColor3f(1.0, 0.0, 0.0);

    /** Desenha poligono com os respectivos vertices */
    glBegin(GL_POLYGON);
    glVertex2i(30,226);  glVertex2i(113,226);
    glVertex2i(113,143); glVertex2i(30,143); 
    glEnd();

    /** Seta o estilo de desenho dos poligonos, neste caso
     * desenha os lados como linhas e as faces de tras */
    glPolygonMode(GL_BACK, GL_FILL);

    /** Seta cor */
    glColor3f(r, g, b);

    /** Desenha poligono */
    glBegin(GL_POLYGON);
        glVertex2i(143,226); glVertex2i(226,226);
        glVertex2i(226,143); glVertex2i(143,143); 
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);  glVertex2i(30,113);
        glColor3f(0.0, 1.0, 0.0);  glVertex2i(113,113);
        glColor3f(0.0, 0.0, 1.0);  glVertex2i(113,30);
        glColor3f(1.0, 1.0, 0.0);  glVertex2i(30,30);
    glEnd();

    /** Seta para o poligono ter usar o padrao nas faces */
    glEnable(GL_POLYGON_STIPPLE);
    glColor3f(1.0, 0.0, 1.0);

    /** Seta que padrao utilizar */
    glPolygonStipple(tux);

    /** Desenha o poligono como faces contendo o padrao em bitmap setado no inicio */
    glBegin(GL_POLYGON);
        glVertex2i(143,113); glVertex2i(226,113);
        glVertex2i(226,30); glVertex2i(143,30); 
    glEnd();

    /** Escreve os comandos do pipeline para o back frame */
    glFlush();

    /** Troca o frame do frame de memoria com o de memoria de video */
    glutSwapBuffers();
}

/**
 * Funcao de tratamento de eventos do teclado 
 * @key valor do byte em ascii correspondente a tecla do evento
 * @x posicao x do ponteiro na tela
 * @y posicao y do ponteiro na tela
 */
void keyboard(unsigned char key, int x, int y){

    switch(key) {
        case 27:
            exit(0);
    }
}

/**
 * Funcao de tratamento de eventos do mouse 
 * @state tipo do evento se apertou o botao ou quando botao sobe
 * @button codigo do botao no evento
 * @x posicao x do ponteiro na tela
 * @y posicao y do ponteiro na tela
 */
void mouse(int button, int state, int x, int y){
    /** Se botao do mouse colhido neste evento for o esquerdo */
    switch(button) {
        case GLUT_LEFT_BUTTON:
            /** Seta varlores para r g b randomico entre 0 e 1.0 */
            if(state == GLUT_DOWN) {
                r=(GLfloat)rand()/(RAND_MAX+1.0);
                g=(GLfloat)rand()/(RAND_MAX+1.0);
                b=(GLfloat)rand()/(RAND_MAX+1.0);
                /** Redesenha a tela */
                glutPostRedisplay();
            }
   }
}

