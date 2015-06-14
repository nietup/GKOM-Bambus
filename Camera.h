#pragma once

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <math.h>

class Camera {
private:
    struct Position {
        float x;
        float y;
        float z;
        float lx;
        float ly;
        float lz;
        float angle;
        float angleVertical;
        float deltaAngle;
        float deltaAngleVertical;
        float deltaMove;
    } position;

    float speed, rotationSpeed;
public:
    enum Action {NORMAL_UP, NORMAL_DOWN, ARROW_UP, ARROW_DOWN};

    Camera();
    ~Camera();

    void update(Action a, int key);
    void refresh();
    void computePos();
    void computeDir();
    void computeDirVertical();

    Position * getPosition() {
        return &position;
    }
};

