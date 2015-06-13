#include "BambooStick.h"

const int BambooStick::leafness = 3;
const float BambooStick::botTopFraction = 1.2f;
const float BambooStick::botHeightFraction = 0.2f;

BambooStick::BambooStick() {
}

BambooStick::BambooStick(GLUquadric * pQobj, float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    qobj = pQobj;
    segments = new std::vector<Segment *>();

    baseSegmentHeight = (float)(rand() % 5 + 3);
    generate();
}

BambooStick::~BambooStick() {
    segments->clear();
    delete segments;
}

void BambooStick::render() {
    float height = 0;
    for (int i = 0; i < segments->size(); i++) {
        glPushMatrix();
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glTranslatef(position.x, position.y + getSegment(i)->height + height, position.z);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        gluCylinder(qobj, getSegment(i)->topRadius, getSegment(i)->botRadius, getSegment(i)->height, 9, 1);
        glPopMatrix();
        height += getSegment(i)->height;
    }
}

void BambooStick::generate() {
    int segmentsNo = rand() % 5 + 3;
    for (int i = 0; i < segmentsNo; i++)
        segments->push_back(generateSegment());
}

BambooStick::Segment * BambooStick::generateSegment() {
    Segment * s = new Segment();
    float hi = baseSegmentHeight + (baseSegmentHeight*0.35f);
    float lo = baseSegmentHeight - (baseSegmentHeight*0.35f);
    s->height = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
    s->botRadius = baseSegmentHeight * botHeightFraction;
    s->topRadius = s->botRadius * botTopFraction;

    if (!(rand() % leafness))
        s->leaf = true;
    else
        s->leaf = false;

    return s;
}

BambooStick::Segment * BambooStick::getSegment(int i) {
    return (*segments)[i];
}