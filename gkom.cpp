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

void init() {
    srand(time(NULL));

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

    camera = new Camera();
    map = new Map();
}

void displayObjects() {
    glPushMatrix();

    map->render();

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
    //const int nrolls = 10000;  // number of experiments
    //const int nstars = 100;    // maximum number of stars to distribute

    //std::default_random_engine generator;
    //std::normal_distribution<double> distribution(2.0, 0.7);

    //int p[10] = {};

    //for (int i = 0; i<nrolls; ++i) {
    //    double number = 2*distribution(generator);
    //    if ((number >= 0.0) && (number<10.0)) ++p[int(number)];
    //}

    //std::cout << "normal_distribution (5.0,2.0):" << std::endl;

    //for (int i = 0; i<10; ++i) {
    //    std::cout << i << "-" << (i + 1) << ": ";
    //    std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
    //}
    //
    //std::cin.get();

    return 0;
}
