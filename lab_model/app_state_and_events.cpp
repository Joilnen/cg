#include "app_state_and_events.h"

AppStateAndEvents::AppStateAndEvents(): MouseToCamera{false}, camera_pos{0, 0, 20}, camera_target{0, 0, -300}, outdoor{true}, step(0.4), wire(false) {

}

AppStateAndEvents::~AppStateAndEvents() {

}

SDL_Event &AppStateAndEvents::getEvent() {
    return event;
}

std::array<GLfloat, 3>& AppStateAndEvents::getCameraPos() {
    return *camera_pos;
}

void AppStateAndEvents::setCameraPos(std::array<GLfloat, 3> &f) {
    *camera_pos = f;
}

void AppStateAndEvents::setCameraTarget(std::array<GLfloat, 3> &f) {
    *camera_target = f;
}

std::array<GLfloat, 3>& AppStateAndEvents::getCameraTarget() {
    return *camera_target;
}


bool AppStateAndEvents::getMouseToCamera() {
    return MouseToCamera;
}


void AppStateAndEvents::setMouseToCamera(bool b) {
    MouseToCamera = b;
}

void AppStateAndEvents::resetOutdoorView() {
    std::array<GLfloat, 3> v1{0, 6, 0};
    std::array<GLfloat, 3> v2{0, 0, 0};
    setCameraPos(v1);
    setCameraTarget(v2);
}

void AppStateAndEvents::resetIndoorView() {
    std::array<GLfloat, 3> v1{0, -3, 0};
    std::array<GLfloat, 3> v2{0, -8, 0};
    setCameraPos(v1);
    setCameraTarget(v2);

}

bool AppStateAndEvents::isOutdoor() {
    return outdoor;
}

void AppStateAndEvents::setIsOutdoor(bool b) {
    outdoor = b;
}

float AppStateAndEvents::getStep() {
    return step;
}

void AppStateAndEvents::setStep(float f) {
    step = f;
}

bool AppStateAndEvents::isWire() {
    return wire;
}

void AppStateAndEvents::setWire(bool f) {
    wire = f;
}

