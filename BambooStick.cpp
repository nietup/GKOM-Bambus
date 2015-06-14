#include "BambooStick.h"
#include <iostream>

const int BambooStick::leafness = 2;
const float BambooStick::botTopFraction = 1.2f;
const float BambooStick::botHeightFraction = 0.2f;
const float BambooStick::maxRotation = 6.f;
Entity::Position BambooStick::rotation = {0, 0, 0};

BambooStick::BambooStick() {
}

BambooStick::BambooStick(GLUquadric * pQobj, std::default_random_engine * generator, float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    qobj = pQobj;
    segments = new std::vector<Segment *>();

    generate(generator);
}

BambooStick::~BambooStick() {
    segments->clear();
    delete segments;
}

void BambooStick::updateRotation() {
    if (abs(BambooStick::rotation.x + Map::windX) <= maxRotation)
        BambooStick::rotation.x += Map::windX;
    else
        Map::updateWind();


    if (abs(BambooStick::rotation.z + Map::windZ) <= maxRotation)
        BambooStick::rotation.z += Map::windZ;

    if (abs(Map::windX) < FLT_EPSILON) {
        if (BambooStick::rotation.x >= 0.025) {
            BambooStick::rotation.x -= 0.02;
        }
        else {
            if (BambooStick::rotation.x <= -0.025)
                BambooStick::rotation.x += 0.02;
            else
                Map::updateWind();
        }
    }

    if (abs(Map::windZ) < FLT_EPSILON) {
        if (BambooStick::rotation.z >= 0.025)
            BambooStick::rotation.z -= 0.02;
        else if(BambooStick::rotation.z <= -0.025)
            BambooStick::rotation.z += 0.02;
    }
}

void BambooStick::render() {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glRotatef(maxRotation*sin((BambooStick::rotation.z / maxRotation)*1.570796), 0, 0, 1);
    glRotatef(maxRotation*sin((BambooStick::rotation.x / maxRotation)*1.570796), 1, 0, 0);
    glTranslatef(-position.x, -position.y, -position.z);
    float height = 0;
    for (int i = 0; i < segments->size(); i++) {
        glPushMatrix();
        glColor3f(139.f / 255.f, 115.f / 255.f, 85.f / 255.f);
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glTranslatef(position.x, position.y + getSegment(i)->height + height, position.z);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        gluCylinder(qobj, getSegment(i)->topRadius, getSegment(i)->botRadius, getSegment(i)->height, 9, 1);
        glPopMatrix();

        if (getSegment(i)->hasLeaf)
            getSegment(i)->leaf->render();

        height += getSegment(i)->height;
    }
    glPopMatrix();
}

void BambooStick::generate(std::default_random_engine * generator) {
    std::normal_distribution<float> heightDistribution(3.0, 0.85);

    baseSegmentHeight = heightDistribution(*generator) + 3.f;
    if (baseSegmentHeight <= 0.0)
        baseSegmentHeight = 1.f;

    int segmentsNo;
    std::normal_distribution<float> segmentsDistribution(5.0, 1.0);

    float number = segmentsDistribution(*generator);

    segmentsNo = (int)number + 3;
    if (segmentsNo <= 0)
        segmentsNo = 1;

    float h = 0;
    for (int i = 0; i < segmentsNo; i++) {
        segments->push_back(generateSegment(h));
        h += getSegment(i)->height;
    }
}

BambooStick::Segment * BambooStick::generateSegment(float y) {
    Segment * s = new Segment();
    float hi = baseSegmentHeight + (baseSegmentHeight*0.35f);
    float lo = baseSegmentHeight - (baseSegmentHeight*0.35f);
    s->height = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
    s->botRadius = baseSegmentHeight * botHeightFraction;
    s->topRadius = s->botRadius * botTopFraction;

    if (!(rand() % leafness)) {
        s->hasLeaf = true;
        s->leaf = new Leaf(s->height, position.x, y, position.z, s->botRadius, s->topRadius);
    }
    else
        s->hasLeaf = false;

    return s;
}

BambooStick::Segment * BambooStick::getSegment(int i) {
    return (*segments)[i];
}