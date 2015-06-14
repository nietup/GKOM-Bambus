#include "Map.h"
#include "Perlin.h"
#include <iostream>

float Map::windX = 0.025f, Map::windZ = 0.5f;

Map::Map(std::default_random_engine * generator) {
    entities = new std::vector<Entity *>();

    qobj = gluNewQuadric();
    Entity * e;

    width = 310.f;
    height = 310.f;
    e = new Floor(-2.f, 0.f, -150.f, width, height);
    entities->push_back(e);

    unsigned int seed = rand() % 256;
    Perlin perlin(seed);
    double px, py, n;
    double pz = (float)(rand() % 1000) / 1000.f;

    for (int x = -15; x < 15; x++) {
        for (int z = 0; z < 30; z++) {
            px = (double)(x*10.f) / ((double)width);
            py = (double)(z*10.f) / ((double)height);

            n = 13 * perlin.noise(px, py, pz);
            n = n - floor(n);

            if (n >= 0.55) {

                float hi = (float)(10 * x) + 5.f;
                float lo = (float)(10 * x) - 4.5f;
                float genX = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
                hi = (float)(10 * z) + 5.f;
                lo = (float)(10 * z) - 4.5f;
                float genZ = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
                e = new BambooStick(qobj, generator, genX, -0.3f, -genZ);
            }
            entities->push_back(e);
        }
    }
}


Map::~Map() {
}

void Map::updateWind() {
    if (!(rand() % 100)) {
        if (!(rand() % 2))
            Map::windX += 0.01f;
        else
            Map::windX -= 0.01f;
    }

    if (!(rand() % 100)) {
        if (!(rand() % 2))
            Map::windZ += 0.01f;
        else
            Map::windZ -= 0.01f;
    }

    if (!(rand() % 3000)) {
        Map::windX = -Map::windX;
    }

    if (!(rand() % 10000)) {
        Map::windZ = -Map::windZ;
    }
}

void Map::render() {

    updateWind();

    for (int i = 0; i < entities->size(); i++)
        (*entities)[i]->render();
}