#include <GL/glut.h>

float angle = 0;

void mydisplay() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    //glutWireTeapot(5.0);	 
   
    // push current state to spin smoothly 
    glPushMatrix();
    glRotatef(angle, 0,1,0);
    // create a torus
    glutWireTorus(7,12,20,10);
    glPopMatrix();

    glFlush();
}

void myidle() {
    angle += 0.1;
    glutPostRedisplay(); // re-execution of display function
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -20, 20); // 垂直投影
    gluLookAt(5,5,5,0,0,0,0,1,0); // 照相機看的角度
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv) {
    glutInitWindowSize(500, 500);
    glutCreateWindow("spin-object");
    glutDisplayFunc(mydisplay);
    glutIdleFunc(myidle);
    init();

    glutMainLoop();
}