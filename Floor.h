#pragma once
#include "Entity.h"

class Floor : public Entity {
private:
    float width, height;
    Position position;
public:
    Floor(float x, float y, float z, float width, float height);      //(x,y,z) of floor center - floor is alway 'XZ' oriented
    ~Floor();

    void render();
};

