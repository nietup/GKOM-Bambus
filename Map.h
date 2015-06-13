#pragma once
#include "Entity.h"
#include "BambooStick.h"
#include "Floor.h"

class Map {
private:
    std::vector<Entity *> * entities;
    GLUquadric * qobj;
public:
    Map();
    ~Map();

    void render();
};

