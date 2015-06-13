#pragma once
#include "Entity.h"

class BambooStick : public Entity{
private:
    static const int leafness;           //denominator in chance of leaf in each segment (where numerator is 1)
    static const float botTopFraction;
    static const float botHeightFraction;

    Position position;
    float baseSegmentHeight;

    struct Segment {
        float botRadius;
        float topRadius;
        float height;
        bool leaf;
    };

    float width, height;
    GLUquadricObj *qobj;
    std::vector<Segment *> * segments;

    void generate(std::default_random_engine * generator);
    Segment * generateSegment();

public:
    BambooStick();
    BambooStick(GLUquadric * q, std::default_random_engine * generator, float x, float y, float z);
    ~BambooStick();

    void render();
    Segment * getSegment(int x);
};

