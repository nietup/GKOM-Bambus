#pragma once
#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

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

