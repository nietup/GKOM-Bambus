#pragma once
#include "Entity.h"
#include <vector>

class BambooStick : public Entity{
private:
    Position position;

    struct Segment {
        float botRadius;
        float topRadius;
        float height;
    };

    float width, height;
    GLUquadricObj *qobj;
    std::vector<Segment *> * segments;

public:
    BambooStick();
    BambooStick(GLUquadric * q, float x, float y, float z);
    ~BambooStick();

    void render();
    void generate();
    Segment * getSegment(int x);
};

