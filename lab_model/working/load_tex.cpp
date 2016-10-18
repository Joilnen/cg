#include <GL/gl.h>
#include <GL/glu.h>
#include <Magick++.h>

#include <iostream>

#include "load_tex.h"

using namespace Magick;
using namespace std;

GLuint texture_id[TEX_NUMBER];

static void loadTexFromId(unsigned int id, char *filename) {
    Image imTex;

    unsigned char *dataTex = nullptr;

    try {
        imTex.magick("PNG");
        imTex.read(filename);

        int w = imTex.columns();
        int h = imTex.rows();

        dataTex = new unsigned char[w * 4 * h];
        imTex.write(0, 0, w, h, "RGBA", CharPixel, dataTex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, dataTex);
        glBindTexture(GL_TEXTURE_2D, texture_id[id]);

        if(dataTex) {
            // glTexImage2D(GL_TEXTURE_2D, 0, 1,
            //           imTex.columns(), imTex.rows(), 0,
            //           GL_RGBA8, GL_UNSIGNED_BYTE, dataTex);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // glActiveTexture(texture_id[DOOR]);
            std::cout << "Carregou textura\n";
            delete dataTex;
        }
    }
    catch(...) {

    }
}

void loadTex() {
    // loadTexFromId(DOOR, "T1_2.png");
    // loadTexFromId(WALL_OUT, "blocks.png");
    Image imTex;

    unsigned char *dataTex = nullptr;

    try {
        imTex.magick("PNG");
        imTex.read("T1_2.png");

        int w = imTex.columns();
        int h = imTex.rows();

        dataTex = new unsigned char[w * 4 * h];
        imTex.write(0, 0, w, h, "RGBA", CharPixel, dataTex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, dataTex);
        glGenTextures(2, texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id[DOOR]);

        if(dataTex) {
            // glTexImage2D(GL_TEXTURE_2D, 0, 1,
            //           imTex.columns(), imTex.rows(), 0,
            //           GL_RGBA8, GL_UNSIGNED_BYTE, dataTex);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // glActiveTexture(texture_id[DOOR]);
            std::cout << "Carregou textura\n";
            delete dataTex;
        }
    }
    catch(...) {

    }

    try {
        imTex.magick("PNG");
        imTex.read("blocks.png");

        int w = imTex.columns();
        int h = imTex.rows();

        dataTex = new unsigned char[w * 4 * h];
        imTex.write(0, 0, w, h, "RGBA", CharPixel, dataTex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, dataTex);
        glBindTexture(GL_TEXTURE_2D, texture_id[WALL_OUT]);

        if(dataTex) {
            // glTexImage2D(GL_TEXTURE_2D, 0, 1,
            //           imTex.columns(), imTex.rows(), 0,
            //           GL_RGBA8, GL_UNSIGNED_BYTE, dataTex);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // glActiveTexture(texture_id[DOOR]);
            std::cout << "Carregou textura\n";
            delete dataTex;
        }
    }
    catch(...) {

    }
}


