#pragma once
#include "Entity.h"
#include "Leaf.h"

class BambooStick : public Entity{
public:
    struct Segment {
        Entity * leaf;
        float botRadius;
        float topRadius;
        float height;
        bool hasLeaf;
    };

    BambooStick();
    BambooStick(GLUquadric * q, std::default_random_engine * generator, float x, float y, float z);
    ~BambooStick();

    void render();
    Segment * getSegment(int x);

private:

    static const int leafness;           //denominator in chance of leaf in each segment (where numerator is 1)
    static const float botTopFraction;
    static const float botHeightFraction;
	static const float maxRotation;

    Position position;
    float baseSegmentHeight;
	

    float width, height;
    GLUquadricObj *qobj;
    std::vector<Segment *> * segments;
	Position dRotation, rotation;

    void generate(std::default_random_engine * generator);
	void updateRotation();
    Segment * generateSegment(float y);                     //global height of segment
};

