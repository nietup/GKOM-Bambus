#pragma once
#include "Entity.h"
#include "BambooStick.h"
#include "Floor.h"
#include "Leaf.h"

class Map {
private:
    std::vector<Entity *> * entities;
    GLUquadric * qobj;
    float width, height;

    void updateWind();
public:
    Map(std::default_random_engine * generator);
    ~Map();

    static float windX, windZ;

    void render();
};

