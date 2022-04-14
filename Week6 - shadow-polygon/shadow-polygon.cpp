#include <stdlib.h>
#include <GL/glut.h>

float light_pos[3] = { 0.0, 10.0, 0.0 };
GLfloat m[16];
float s_angle = 0.0;
float vertices[8][3] = { {-2,-2,2},{-2,2,2},{2,2,2},{2,-2,2},{-2,-2,-2},{-2,2,-2},{2,2,-2},{2,-2,-2} };

void mydisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 10, 0);
	glRotatef(s_angle, 0, 1, 0);
	//glutSolidTeapot(3);
	glBegin(GL_QUADS);
		// quad 1
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[1]);
		// quad 2
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[7]);
		glVertex3fv(vertices[6]);
		// quad 3
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[7]);
		// quad 4
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[5]);
		// quad 5
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[7]);
		// quad 6
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[1]);
	glEnd();
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(light_pos[0], light_pos[1], light_pos[2]);
	glMultMatrixf(m);
	glTranslatef(-light_pos[0], -light_pos[1], -light_pos[2]);
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(s_angle, 0, 1, 0);
	//glutSolidTeapot(3);
	glBegin(GL_QUADS);
		// quad 1
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[1]);
		// quad 2
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[7]);
		glVertex3fv(vertices[6]);
		// quad 3
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[7]);
		// quad 4
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[5]);
		// quad 5
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[7]);
		// quad 6
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[1]);
	glEnd();
	glPopMatrix();

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
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	for (int i = 0; i < 16; i++) m[i] = 0.0;
	m[0] = m[5] = m[10] = 1.0;
	m[7] = -1.0 / light_pos[1];
}

void main(int argc, char** argv) {
	glutInitWindowSize(500, 500);
	glutCreateWindow("1092923");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(rotate);
	init();

	glutMainLoop();
}