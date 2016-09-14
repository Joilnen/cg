#include <GL/gl.h>
#include <GL/glu.h>
#include <Magick++.h>

#include <iostream>

#include "load_tex.h"

using namespace Magick;
using namespace std;

void loadTex() {
    Image imTex;
    extern GLuint texture_id;

    unsigned char *dataTex = nullptr;
    try {
        imTex.magick("PNG");
        imTex.read("T1_2.png");

        int w = imTex.columns();
        int h = imTex.rows();

        dataTex = new unsigned char[w * 4 * h];
        imTex.write(0, 0, w, h, "RGBA", CharPixel, dataTex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, dataTex);
    }
    catch(Exception &e) {
        std::cerr << "Noop\n";
    }

    if(dataTex) {
        // glTexImage2D(GL_TEXTURE_2D, 0, 1,
        //           imTex.columns(), imTex.rows(), 0,
        //           GL_RGBA8, GL_UNSIGNED_BYTE, dataTex);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        // glActiveTexture(texture_id);
        std::cout << "Carregou textura\n";
    }
}

