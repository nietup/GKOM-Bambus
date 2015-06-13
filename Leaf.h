#pragma once
#include "BambooStick.h"
class Leaf : public Entity {
private:
    float height;
    float baseWidth, curveWidth;
    float length;
    float x, y, z;
    float rotation;

public:
    Leaf(float segmentHeight, float x, float y, float z, float botR, float topR);              //y is segment bot location, x and z are cener of base
    ~Leaf();

    void render();
};

