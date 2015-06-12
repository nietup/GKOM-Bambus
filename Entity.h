#pragma once
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
class Entity {
protected:
    struct Position {
        float x;
        float y;
        float z;
    };
public:
    Entity();
    ~Entity();
    virtual void render() = 0;
};

