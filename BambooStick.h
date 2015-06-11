#pragma once
#include "Entity.h"

class BambooStick : public Entity{
private:
    float width, height;
    GLUquadricObj *qobj;

    struct Position {
        float x;
        float y;
        float z;
    } position;

public:
    BambooStick();
    BambooStick(float x, float y, float z);
    ~BambooStick();

    void render();
};

