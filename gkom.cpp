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

int width;
int height;
double lasttime;
double timediff;
double fps;
std::vector<Entity *> * entities;
struct Position {
    float x;
    float y;
    float z;
    float lx;
    float ly;
    float lz;
    float angle;
    float angleVertical;
    float deltaAngle;
    float deltaAngleVertical;
    float deltaMove;
} cameraPosition;

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
    GLUquadric * qobj = gluNewQuadric();
    Entity * e;
    e = new BambooStick(qobj, 10, 0, -30);
    entities->push_back(e);
    e = new BambooStick(qobj, -10, 0, -30);
    entities->push_back(e);
    e = new Floor(0.f, 0.f, -30.f, 10.f, 10.f);
    entities->push_back(e);
    cameraPosition.z = 10.f;
    cameraPosition.y = 1.f;
    cameraPosition.x = cameraPosition.lx = cameraPosition.angleVertical = cameraPosition.ly = cameraPosition.angle = cameraPosition.deltaAngle = cameraPosition.deltaAngleVertical = cameraPosition.deltaMove = 0;
    cameraPosition.lz = -10.f;
}

void displayObjects() {

    glPushMatrix();

    for (int i = 0; i < entities->size(); i++)
        (*entities)[i]->render();

    glPopMatrix();
}

void computePos(float deltaMove) {
    cameraPosition.x += deltaMove * cameraPosition.lx * 0.1f;
    cameraPosition.y += deltaMove * cameraPosition.ly * 0.1f;
    cameraPosition.z += deltaMove * cameraPosition.lz * 0.1f;
}

void computeDir(float deltaAngle) {
    cameraPosition.angle += deltaAngle;
    cameraPosition.lx = sin(cameraPosition.angle);
    cameraPosition.lz = -cos(cameraPosition.angle);
}

void computeDirVertical(float deltaAngle) {
    if (deltaAngle >= 0) {
        if (cameraPosition.angleVertical < 3.14f / 2.f) {
            cameraPosition.angleVertical += deltaAngle;
            cameraPosition.ly = 2 * sin(cameraPosition.angleVertical);
        }
        else {
            cameraPosition.ly = 5.f;
        }
    }
    else {
        if (cameraPosition.angleVertical > -3.14f / 2.f) {
            cameraPosition.angleVertical += deltaAngle;
            cameraPosition.ly = 2 * sin(cameraPosition.angleVertical);
        }
        else {
            cameraPosition.ly = -5.f;
        }
    }
}

void render() {

    if (cameraPosition.deltaMove)
        computePos(cameraPosition.deltaMove);
    if (cameraPosition.deltaAngle)
        computeDir(cameraPosition.deltaAngle);
    if (cameraPosition.deltaAngleVertical)
        computeDirVertical(cameraPosition.deltaAngleVertical);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //wypelnienie bufora domyslnymi wartosciami
    glLoadIdentity();

    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
              cameraPosition.x + cameraPosition.lx, cameraPosition.y + cameraPosition.ly, cameraPosition.z + cameraPosition.lz,
              0.0f, 1.0f, 0.0f);

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

    switch (key) {
        case 'w':
            cameraPosition.deltaMove = 1.8f;
            break;
        case 's':
            cameraPosition.deltaMove = -0.5f;
            break;
    }
}

void releaseNormalKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 's':
            cameraPosition.deltaMove = 0;
            break;
    }
}

void pressKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT:
            cameraPosition.deltaAngle = -0.01f;
            break;
        case GLUT_KEY_RIGHT:
            cameraPosition.deltaAngle = 0.01f;
            break;
        case GLUT_KEY_UP:
            cameraPosition.deltaAngleVertical = 0.01f;
            break;
        case GLUT_KEY_DOWN:
            cameraPosition.deltaAngleVertical = -0.01f;
            break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            cameraPosition.deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            cameraPosition.deltaAngleVertical = 0.0f;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);      //pojedyncze buforowanie - single, double; depth - zbufor

    glutInitWindowPosition(0, 0);
    width = 1024;
    height = 512;
    glutInitWindowSize(1024, 512);

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

    init();

    glutMainLoop();

    return 0;
}
