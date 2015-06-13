#include "Camera.h"


Camera::Camera() {
    position.z = 10.f;
    position.y = 1.f;
    position.x = position.lx = position.angleVertical = position.ly = position.angle = position.deltaAngle = position.deltaAngleVertical = position.deltaMove = 0;
    position.lz = -10.f;
}


Camera::~Camera() {
}

void Camera::computePos() {
    position.x += position.deltaMove * position.lx * 0.1f;
    position.y += position.deltaMove * position.ly * 0.1f;
    position.z += position.deltaMove * position.lz * 0.1f;
}

void Camera::computeDir() {
    position.angle += position.deltaAngle;
    position.lx = sin(position.angle);
    position.lz = -cos(position.angle);
}

void Camera::computeDirVertical() {
    if (position.deltaAngleVertical >= 0) {
        if (position.angleVertical < 3.14f / 2.f) {
            position.angleVertical += position.deltaAngleVertical;
            position.ly = 2 * sin(position.angleVertical);
        }
        else {
            position.ly = 5.f;
        }
    }
    else {
        if (position.angleVertical > -3.14f / 2.f) {
            position.angleVertical += position.deltaAngleVertical;
            position.ly = 2 * sin(position.angleVertical);
        }
        else {
            position.ly = -5.f;
        }
    }
}

void Camera::refresh() {
    //if (position.deltaMove != 0)
        computePos();
    //if (position.deltaAngle != 0)
        computeDir();
    //if (position.deltaAngleVertical != 0)
        computeDirVertical();

    gluLookAt(position.x, position.y, position.z,
              position.x + position.lx, position.y + position.ly, position.z + position.lz,
              0.0f, 1.0f, 0.0f);
}

void Camera::update(Action a, int key) {
    if (a == NORMAL_DOWN) {
        switch (key) {
            case 'w':
                position.deltaMove = 1.8f;
                break;
            case 's':
                position.deltaMove = -0.5f;
                break;
        }
    }
    if (a == NORMAL_UP) {
        switch (key) {
            case 'w':
            case 's':
                position.deltaMove = 0;
                break;
        }
    }
    if (a == ARROW_DOWN) {
        switch (key) {
            case GLUT_KEY_LEFT:
                position.deltaAngle = -0.01f;
                break;
            case GLUT_KEY_RIGHT:
                position.deltaAngle = 0.01f;
                break;
            case GLUT_KEY_UP:
                position.deltaAngleVertical = 0.01f;
                break;
            case GLUT_KEY_DOWN:
                position.deltaAngleVertical = -0.01f;
                break;
        }
    }
    if (a == ARROW_UP) {
        switch (key) {
            case GLUT_KEY_LEFT:
            case GLUT_KEY_RIGHT:
                position.deltaAngle = 0.0f;
                break;
            case GLUT_KEY_UP:
            case GLUT_KEY_DOWN:
                position.deltaAngleVertical = 0.0f;
                break;
        }
    }
}