#include "object.h"

Object::Object() {

}

Object::~Object() {

}

void Object::addFace(Face f) {
    faces.push_back(f);
}

void Object::deleteFace(int index) {

}

void Object::setMode(ModeDraw m) {

}

void Object::rotate(int index) {

}


void Object::draw() {
    for (auto &f : faces)
        f.draw();
}


