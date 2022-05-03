#include <stdlib.h>
#include <GL/glut.h>

float s_angle = 0.0;

void mydisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);
	//glTranslatef(0, 10, 0);
	//glPushMatrix();
	//glRotatef(s_angle, 0, 1, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position0[4] = { 10, 20, -50, 1 };
	GLfloat ambient0[4] = { 0.1, 0.1, 0.1, 1 };
	GLfloat diffuse0[4] = { 1, 1, 0, 1 };
	GLfloat specular0[4] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glEnable(GL_LIGHT1);

	GLfloat position1[4] = { 10, 20, -10, 1 };
	GLfloat ambient1[4] = { 0.1, 0.1, 0.1, 1 };
	GLfloat diffuse1[4] = { 1, 0, 1, 1 };
	GLfloat specular1[4] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	
	

	glColor3f(1, 1, 0);
	glutSolidTeapot(8);
	//glPopMatrix();
	
	glFlush();
}
void rotate()
{
	if (s_angle >= 360) 
		s_angle = 0.0;
	s_angle += 0.1;
	glutPostRedisplay();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
}

void main(int argc, char** argv) {
	glutInitWindowSize(500, 500);
	glutCreateWindow("1092923");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(rotate);
	init();

	glutMainLoop();
}