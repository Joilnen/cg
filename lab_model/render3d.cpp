/***********************
 * Aluno Joilnen Leite
 **********************/
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <sys/time.h>
#include "render3d.h"
#include "imgui.h"

#include "palace.h"
#include "func.h"
#include "app_state_and_events.h"

float rotateSpeed = 180.0f; /* degrees per second */
bool pause = true;

#define INPUT KeyPressMask | ExposureMask 

GLfloat cam_inc = 3;
GLfloat cam_inc2 = 0;
SDL_Window *lpwin = NULL;

void SetUpLights() {
    float pos[] = {10, 10, 10, 0};
    float ambient[] = {0.3, 0.3, 0.3, 1};
    float white[] = {1, 1, 1, 1};

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHT0);
}

void DrawScene(AppStateAndEvents &ae, float dT) {
    static float angle = 180.0f;
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        ae.getCameraPos()[0], ae.getCameraPos()[1], ae.getCameraPos()[2],
        ae.getCameraTarget()[0], ae.getCameraTarget()[1], ae.getCameraTarget()[2],
        0, 0, 1
    );

    glPushMatrix();
    glLoadIdentity();
    SetUpLights();
    glPopMatrix();

    if (!pause)
        angle += rotateSpeed * dT;

    glRotatef(angle, 0, 0, 1);
    DrawAllMeshes();
}

void SetUpOpenGL() {
    int windowwidth, windowheight;
    if(lpwin)
        SDL_GetWindowSize(lpwin, &windowwidth, &windowheight);
    else {
        windowwidth = 1024; windowheight = 600;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float) windowwidth / (float) windowheight, 0.15, 251.0);
    glViewport(0, 0, windowwidth, windowheight);

    glMatrixMode(GL_MODELVIEW);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);

    glEnable(GL_CULL_FACE);

    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glColor4f(1, 1, 1, 1);
}

float GetTimeInterval() {
    static struct timeval time = {0, 0};
    static struct timeval last = {0, 0};
    int sec, usec;


    gettimeofday(&time, NULL);

    sec = time.tv_sec - last.tv_sec;
    usec = time.tv_usec - last.tv_usec;


    last.tv_sec = time.tv_sec;
    last.tv_usec = time.tv_usec;

    sec *= 1000000;
    sec += usec;

    return (float) sec / 1.0e6;
}

void Resize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float) width / (float) height, 0.15, 251.0);
    glViewport(0, 0, width, height);
}

/*******==================******/

static void drawCube(float orientation[3], float position[3], float scale[3], float tone) {
    // vertices 
    GLfloat vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    // Define color gray
    GLfloat colors[72];
    for(int i = 0 ; i < 72 ; i++){
        colors[i] = tone;
    }

    glPushMatrix();
        glRotatef(orientation[0], 1, 0, 0);
        glRotatef(orientation[1], 0, 1, 0);
        glRotatef(orientation[2], 0, 0, 1);
        glTranslatef(position[0], position[1], position[2]);
        glScalef(scale[0], scale[1], scale[2]);
        
        //We have a color array and a vertex array 
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);

        //Send data : 24 vertices 
        glDrawArrays(GL_QUADS, 0, 24);

        //Cleanup states 
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

static void drawSphere(double r, int lats, int longs, int x, int y, int z){
    glPushMatrix();
        glTranslatef(x, y+0.15, z);
        glScalef(0.47, 0.47, 0.47);

        int i, j;

        for(i = 0; i <= lats; i++){
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            double z0  = sin(lat0);
            double zr0 =  cos(lat0);

            double lat1 = M_PI * (-0.5 + (double) i / lats);
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            glColor3f(1, 0.4, 0.1);
            glBegin(GL_QUAD_STRIP);

            for(j = 0; j <= longs; j++) {
                double lng = 2 * M_PI * (double) (j - 1) / longs;
                double x = cos(lng);
                double y = sin(lng);

                glNormal3f(x * zr0, y * zr0, z0);
                glVertex3f(x * zr0, y * zr0, z0);
                glNormal3f(x * zr1, y * zr1, z1);
                glVertex3f(x * zr1, y * zr1, z1);
            }
            glEnd();
        }
    glPopMatrix();
}

float rotateCube = 0; // Apply rotation on cube

void init_render() {
    SetUpOpenGL();

    InitMesh();

    GetTimeInterval();
}

float t, T = 0.0;
void render(SDL_Window *win, AppStateAndEvents &ae) {
    // Rendering
    lpwin = win;
    ImVec4 clear_color = ImColor(114, 144, 154, 0);
    GLint display_w, display_h;
    SDL_GetWindowSize(win, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (double)display_w / (double)display_h, 0.1, 3000);

    glMatrixMode(GL_MODELVIEW);

    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /****
    glLoadIdentity();

    // Positions the "camera"
    // Both respectively X, Y and Z
    int orientation[3] = { 60, 0, 0 };
    int position[3] = { 0, -20, -15 };

    glRotatef(orientation[0], 1, 0, 0);
    glRotatef(orientation[1], 0, 1, 0);
    glRotatef(orientation[2], 0, 0, 1);
    glTranslatef(position[0], position[1], position[2]);

    // Draw objects
    float orientationFloor[3] = { 0, 0, 0 }; // Radians
    float positionFloor[3] = { 0, 0, 0 };
    float scaleFloor[3] = { 15, 0.05, 13 };
    drawCube(orientationFloor, positionFloor, scaleFloor, 0.1);

    drawSphere(1, 10, 10, 3, 0, 0);

    float orientationCube[3] = { 0, rotateCube, 0 }; // Radians
    float positionCube[3] = { 0, 1, 0 };
    float scaleCube[3] = { 1, 1 ,1 };
    drawCube(orientationCube, positionCube, scaleCube, 0.2);
    rotateCube += 0.2;

    T += (t = GetTimeInterval());
    ****/

    DrawScene(ae, t);

}
