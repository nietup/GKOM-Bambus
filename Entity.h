#pragma once
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
class Entity {
public:
    Entity();
    ~Entity();
    virtual void render() = 0;
};

