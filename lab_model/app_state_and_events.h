#ifndef APP_STATE_AND_EVENTS
#define APP_STATE_AND_EVENTS


#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <array>

class AppStateAndEvents {
    std::array<GLfloat, 3> camera_pos[3], camera_target[3];
    SDL_Event event;
    bool MouseToCamera;
    bool outdoor;
    float step;
    bool wire;
    public:
        AppStateAndEvents();
        ~AppStateAndEvents();
        std::array<GLfloat, 3>& getCameraPos();
        void setCameraPos(std::array<GLfloat, 3>&);

        std::array<GLfloat, 3>& getCameraTarget();
        void setCameraTarget(std::array<GLfloat, 3>&);

        float getStep();
        void setStep(float f);

        bool isWire();
        void setWire(bool f);

        SDL_Event &getEvent();
        bool getMouseToCamera();
        void setMouseToCamera(bool);

        void resetOutdoorView();
        void resetIndoorView();
        bool isOutdoor();
        void setIsOutdoor(bool);
};

#endif
