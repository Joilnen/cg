#include "face.h"

Face::Face() {
    X(vertices[0]) = -30;
    Y(vertices[0]) = -30;
    Z(vertices[0]) = -10;

    X(vertices[1]) = 30;
    Y(vertices[1]) = -30;
    Z(vertices[1]) = -10;

    X(vertices[2]) = 30;
    Y(vertices[2]) = 30;
    Z(vertices[2]) = -10;

    X(vertices[3]) = -30;
    Y(vertices[3]) = 30;
    Z(vertices[3]) = -10;
}

Face::~Face() {

}

void Face::draw() {

}

void Face::scale(float x, float y) {

}

void Face::raotate(float x, float y, float z) {

}

void Face::setMode(ModeDraw m) {

}

vec<float, 3> &Face::getNormal() {
    return normal;
}


