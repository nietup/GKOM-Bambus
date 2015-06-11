/*
 * GKOM Bamboo project
 */

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>
#include <vector>
#include "Entity.h"
#include "BambooStick.h"

std::vector<Entity *> * entities;

void init() {
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};			//mat - wspolczynniki odbicia
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0.0, 0.0, 10.0, 1.0};
    GLfloat lm_ambient[] = {0.2, 0.2, 0.2, 1.0};			//swiatlo rozproszone

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    entities = new std::vector<Entity *>();
    Entity * bs;
    bs = new BambooStick(0, 0, -30);
    entities->push_back(bs);
    bs = new BambooStick(-10, 0, -30);
    entities->push_back(bs);
}

void displayObjects() {
    /*
    wspolzedne:
    0 0 w srodku okna
    x ->
    y ^
    */

    GLfloat torus_diffuse[] = {0.7, 0.7, 0.0, 1.0};
    GLfloat cube_diffuse[] = {0.0, 0.7, 0.7, 1.0};
    GLfloat sphere_diffuse[] = {0.7, 0.0, 0.7, 1.0};
    GLfloat octa_diffuse[] = {0.7, 0.4, 0.4, 1.0};

    //calosc
    glPushMatrix();

    //plane
    glPushMatrix();

    for (int i = 0; i < entities->size(); i++)
        (*entities)[i]->render();

    //fin plane
    glPopMatrix();

    //fin calosc
    glPopMatrix();
}

void display() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//wypelnienie bufora domyslnymi wartosciami
    displayObjects();

    glFlush();													//wywalenie wszystkich oczekujacych wejsc
    glutSwapBuffers();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)												//width || heigth
{
    if (h > 0 && w > 0) {
        int width = w;
        int height = h;
        glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 10000.0);
        glMatrixMode(GL_MODELVIEW);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		//pojedyncze buforowanie - single, double; depth - zbufor

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1024, 512);

    glutCreateWindow("GKOM: Bamboo Ulimate Elite");

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

    return 0;
}
