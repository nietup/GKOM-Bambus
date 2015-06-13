#include "Leaf.h"
#include <iostream>

Leaf::Leaf(float segmentHeight, float pX, float pY, float pZ, float botR, float topR) {
    baseWidth = 0.05f * segmentHeight;
    curveWidth = 6.f * baseWidth;
    height = segmentHeight / 6.f;
    rotation = float(rand() % 360);
    float hi = segmentHeight;
    float lo = 0;
    y = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
    float r = botR + ((topR-botR) / segmentHeight)*y;
    y += pY;
    x = -r * sin((rotation / 360.f)*2.f*3.1415926f) + pX;
    z = -r * cos((rotation / 360.f)*2.f*3.1415926f) + pZ;
    hi = segmentHeight + (segmentHeight*0.35f);
    lo = segmentHeight - (segmentHeight*0.35f);
    length = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
}


Leaf::~Leaf() {
}

void Leaf::render() {
    glPushMatrix();
    glColor3f(69.f / 255.f, 139.f / 255.f, 0.f);
    glTranslatef(x, y, z);
    glRotatef(rotation, 0.f, 1.f, 0.f);

    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-baseWidth / 2.f, 0.f, 0.f);
    glVertex3f(baseWidth / 2.f, 0.f, 0.f);
    glVertex3f(curveWidth / 2.f, height, -length / 4.f);
    glVertex3f(-curveWidth / 2.f, height, -length / 4.f);
    glEnd(); //End quadrilateral coordinates

    glBegin(GL_TRIANGLES);
    glVertex3f(-curveWidth / 2.f, height, -length / 4.f);
    glVertex3f(curveWidth / 2.f, height, -length / 4.f);;
    glVertex3f(0.f, height / 2.f, -length);
    glEnd();

    glPopMatrix();
}

