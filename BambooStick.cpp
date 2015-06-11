#include "BambooStick.h"

BambooStick::BambooStick() {
    position.x = 30;
    position.y = 30;
    position.z = 100;
}

BambooStick::BambooStick(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}


BambooStick::~BambooStick() {
}


void BambooStick::render() {

    glPushMatrix();
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glTranslatef(position.x, position.y, position.z);
    glRotatef(99.f, 1.f, 0.f, 0.f);
    gluCylinder(qobj, 2.0, 1.0, 10.0, 9, 1);
    glPopMatrix();

    glPushMatrix();
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glTranslatef(position.x, position.y + 5.f, position.z);
    glRotatef(99.f, 1.f, 0.f, 0.f);
    gluCylinder(qobj, 2.0, 1.0, 5.0, 9, 1);
    glPopMatrix();

}