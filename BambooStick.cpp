#include "BambooStick.h"

BambooStick::BambooStick() {
    position.x = 30;
    position.y = 30;
    position.z = 100;
}

BambooStick::BambooStick(GLUquadric * pQobj, float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    qobj = pQobj;
    segments = new std::vector<Segment *>();

    generate();
}


BambooStick::~BambooStick() {
}


void BambooStick::render() {

    //glPushMatrix();
    ////qobj = gluNewQuadric();
    //gluQuadricNormals(qobj, GLU_SMOOTH);
    //glTranslatef(position.x, position.y, position.z);
    //glRotatef(99.f, 1.f, 0.f, 0.f);
    //gluCylinder(qobj, 2.0, 1.0, 10.0, 9, 1);
    //glPopMatrix();

    //glPushMatrix();
    //// qobj = gluNewQuadric();
    //gluQuadricNormals(qobj, GLU_SMOOTH);
    //glTranslatef(position.x, position.y + 5.f, position.z + 0.5f);
    //glRotatef(99.f, 1.f, 0.f, 0.f);
    //gluCylinder(qobj, 2.0, 1.0, 5.0, 9, 1);
    //glPopMatrix();

    float height = 0;
    for (int i = 0; i < segments->size(); i++) {
        glPushMatrix();
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glTranslatef(position.x,
                     position.y + getSegment(i)->height + height,
                     position.z + 0.5f*getSegment(i)->botRadius);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        gluCylinder(qobj, getSegment(i)->topRadius, getSegment(i)->botRadius, getSegment(i)->height, 9, 1);
        glPopMatrix();
        height += getSegment(i)->height/2.f;
    }


}

void BambooStick::generate() {
    Segment * s = new Segment();
    s->botRadius = 1.f;
    s->topRadius = 2.f;
    s->height = 5.f;
    segments->push_back(s);

    s = new Segment();
    s->botRadius = 1.f;
    s->topRadius = 2.f;
    s->height = 3.f;
    segments->push_back(s);

    s = new Segment();
    s->botRadius = 1.f;
    s->topRadius = 2.f;
    s->height = 4.f;
    segments->push_back(s);
}

BambooStick::Segment * BambooStick::getSegment(int i) {
    return (*segments)[i];
}