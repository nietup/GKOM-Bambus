#include "Floor.h"


Floor::Floor(float x, float y, float z, float width, float height) : width(width), height(height) {
    position.x = x;
    position.y = y;
    position.z = z;
}


Floor::~Floor() {
}

void Floor::render() {
    glPushMatrix(); 
    glColor3f(0 / 255.f, 51.f / 255.f, 0 / 255.f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(position.x - width / 2.f, position.y, position.z + height / 2.f);
    glVertex3f(position.x - width / 2.f, position.y, position.z - height / 2.f);
    glVertex3f(position.x + width / 2.f, position.y, position.z - height / 2.f);
    glVertex3f(position.x + width / 2.f, position.y, position.z + height / 2.f);
    glEnd(); //End quadrilateral coordinates
    glPopMatrix();
}