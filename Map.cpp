#include "Map.h"


Map::Map(std::default_random_engine * generator) {
    entities = new std::vector<Entity *>();

    qobj = gluNewQuadric();
    Entity * e;

    e = new Floor(-2.f, 0.f, -30.f, 100.f, 100.f);
    entities->push_back(e);

    for (int x = -5; x < 5; x++) {
        for (int z = -8; z < 2; z++) {
            if ((z + 8) % 2)
                e = new BambooStick(qobj, generator, 10 * x + 5, 0, 10 * z);
            else
                e = new BambooStick(qobj, generator,  10 * x, 0, 10 * z);

            entities->push_back(e);
        }
    }
}


Map::~Map() {
}

void Map::render() {
    for (int i = 0; i < entities->size(); i++)
        (*entities)[i]->render();
}