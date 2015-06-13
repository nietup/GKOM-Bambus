#pragma once
#include "Entity.h"
#include "BambooStick.h"
#include "Floor.h"
#include "Leaf.h"

class Map {
private:
    std::vector<Entity *> * entities;
    GLUquadric * qobj;
public:
    Map(std::default_random_engine * generator);
    ~Map();

    void render();
};

