#include "modeler.h"


Modeler::Modeler(): editing(false) {

}

Modeler::~Modeler() {

}

void Modeler::createObject(ObjectType ot) {
    if(ot == ObjectType::PLAN) {
        createPlan();
    }
    else if(ot == ObjectType::CUBE) {
        createCube();
    }
}

bool Modeler::isEditing() {

}

void Modeler::draw() {
    for(auto &a : objects)
        a.draw();
}

void Modeler::selectObject(int i) {

}

int Modeler::getObjectIndex(string &s) {

}

void Modeler::deleteObject(string &s) {

}

void Modeler::deleteObject(int i) {

}

void Modeler::addObject(Object o) {
    objects.push_back(o);
}

void Modeler::setEditObject(string &s) {

}

void Modeler::exitEditMode() {

}

void Modeler::createPlan() {
    Face f;
    Object o;
    o.addFace(f);
    addObject(o);
}

void Modeler::createCube() {

}


