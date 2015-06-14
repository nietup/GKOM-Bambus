#include "BambooStick.h"

const int BambooStick::leafness = 3;
const float BambooStick::botTopFraction = 1.2f;
const float BambooStick::botHeightFraction = 0.2f;
const float BambooStick::maxRotation = 33.f;

BambooStick::BambooStick() {
}

BambooStick::BambooStick(GLUquadric * pQobj, std::default_random_engine * generator, float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
	rotation.x = rotation.z = 0;
	dRotation.x = dRotation.z = 1.f;
    qobj = pQobj;
    segments = new std::vector<Segment *>();

    generate(generator);
}

BambooStick::~BambooStick() {
    segments->clear();
    delete segments;
}

void BambooStick::updateRotation() {

	rotation.x += dRotation.x;
	rotation.z += dRotation.z;
	if (rotation.x >= maxRotation)
		rotation.x = maxRotation;
	if (rotation.z >= maxRotation)
		rotation.z = maxRotation;
}

void BambooStick::render() {
	updateRotation();
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	glRotatef(maxRotation*sin((rotation.z / maxRotation)*1.570796), 0, 0, 1);
	glRotatef(maxRotation*sin((rotation.x / maxRotation)*1.570796), 1, 0, 0);
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
    std::normal_distribution<float> segmentsDistribution(2.0, 0.75);

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