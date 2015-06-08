/*
 * GKOM Bamboo project
 */

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <iostream>

void init()
{
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };			//mat - wspolczynniki odbicia
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 1.0 };			//swiatlo rozproszone

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
}

void displayObjects(int nFrame)
{
	/*
	wspolzedne:
	0 0 w srodku okna
	x ->
	y ^
	*/

	GLfloat torus_diffuse[] = { 0.7, 0.7, 0.0, 1.0 };
	GLfloat cube_diffuse[] = { 0.0, 0.7, 0.7, 1.0 };
	GLfloat sphere_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
	GLfloat octa_diffuse[] = { 0.7, 0.4, 0.4, 1.0 };

	//calosc
	glPushMatrix();
	glRotatef(nFrame, 1.0, 0.0, 0.0);

    //plane
    glPushMatrix ();

    glBegin (GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f (-100.f, -1.0f, -100.f);
    glVertex3f (-100.f, -1.0f, 100.f);
    glVertex3f (100.f, -1.0f, 100.f);
    glVertex3f (100.f, -1.0f, -100.f);
    glEnd (); //End quadrilateral coordinates

    //fin plane
    glPopMatrix ();

	//fin calosc
	glPopMatrix();
}

void display()
{
	static int nFrame = 0, tmp = 0;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRotatef(1.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//wypelnienie bufora domyslnymi wartosciami
	displayObjects(nFrame);

	glFlush();													//wywalenie wszystkich oczekujacych wejsc
	glutSwapBuffers();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

    ++tmp;
    tmp %= 100;

    if (tmp == 0) {
        ++nFrame;
        std::cout << "fresfes" << std::endl;
    }
    else {
        std::cout << tmp << " - " << (tmp == 0) << std::endl;
    }

    nFrame %= 360;

    //::cout << tmp << std::endl;

}

void reshape(GLsizei w, GLsizei h)												//width || heigth
{
	if (h > 0 && w > 0) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (w <= h) {															//glortho - rzutowanie prostokatne | glfrustum - rzutpwanie perspektywiczne
																				//we frustum z min to odleglosc od srodka rzutowania do plyty ekranu, z max to koniec sceny
			glFrustum(-2.25, 2.25, -2.25*h/w, 2.25*h/w, 1.0, 10.0);
            //glFrustum (-1.0, 1.0, -1.0*(h / w), 1.0*(h / w), 1.0, 10.0);
		}
		else {
			glFrustum(-2.25*w/h, 2.25*w/h, -2.25, 2.25, 1.0, 10.0);
            //glFrustum (-1.0*(w / h), 1.0*(w / h), -1.0, 1.0, 1.0, 10.0);
		}

		glTranslatef(0.0, 0.0, -3.0);
		glMatrixMode(GL_MODELVIEW);
	}

}

int main(int argc, char** argv)
{
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
