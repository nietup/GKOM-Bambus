/*
* GKOM Bamboo project
*/

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>
#include "Entity.h"
#include "BambooStick.h"
#include "Floor.h"
#include "Camera.h"
#include "Map.h"
#include <string>

int width;
int height;
double lasttime;
double timediff;
double fps;
Camera * camera;
Map * map;
std::default_random_engine * generator;

void init() {
    srand(time(NULL));

    //GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};			//mat - wspolczynniki odbicia
    //GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lm_ambient[] = {0.2, 0.2, 0.2, 1.0};			//swiatlo rozproszone
    GLfloat light_position[] = {0.0, 10.0, 10.0, 1.0};

    //ambient diffuse speculear shineieesss
    //0.25	0.25	0.25	0.4	0.4	0.4	0.774597	0.774597	0.774597	0.6
    GLfloat mat_ambient[] = {0.25	,0.25	,0.25, 1.0};
    GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat mat_specular[] = {0.774597,	0.774597,	0.774597, 1.0};
    GLfloat shiniess = 0.6;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0 * shiniess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

    glShadeModel(GL_SMOOTH);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    camera = new Camera();
    generator = new std::default_random_engine();
    map = new Map(generator);
}

void displayObjects() {
    glPushMatrix();

    map->render();
    BambooStick::updateRotation();

    glPopMatrix();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //wypelnienie bufora domyslnymi wartosciami
    glLoadIdentity();

    camera->refresh();
    displayObjects();

    glFlush();                                              //wywalenie wszystkich oczekujacych wejsc
    glutSwapBuffers();

    timediff = GetTickCount() - lasttime;
    if (timediff < 16) {
        Sleep(16 - timediff);
    }
    fps = (timediff / 16) * 60;
    lasttime += timediff;
}

void reshape(GLsizei w, GLsizei h)                              //width || heigth
{
    if (h > 0 && w > 0) {
        width = w;
        height = h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 10000.0);
        glMatrixMode(GL_MODELVIEW);
    }
}

void pressNormalKey(unsigned char key, int x, int y) {
    if (key == 27)              //escape
        exit(0);

    camera->update(Camera::NORMAL_DOWN, key);
}

void releaseNormalKey(unsigned char key, int x, int y) {
    camera->update(Camera::NORMAL_UP, key);
}

void pressKey(int key, int xx, int yy) {
    camera->update(Camera::ARROW_DOWN, key);
}

void releaseKey(int key, int x, int y) {
    camera->update(Camera::ARROW_UP, key);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);      //pojedyncze buforowanie - single, double; depth - zbufor

    glutInitWindowPosition(0, 0);
    width = 1400;
    height = 700;
    glutInitWindowSize(width, height);

    glutCreateWindow("GKOM: Bamboo Ulimate Elite");

    glutIdleFunc(render);
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(pressNormalKey);
    glutKeyboardUpFunc(releaseNormalKey);
    glutSpecialFunc(pressKey);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    init();

    glutMainLoop();

    return 0;
}
