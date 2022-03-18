#include <GL/glut.h>

#define TEAPOT 1

int size = 10;

void mydisplay() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void mouse_callback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON || state == GLUT_DOWN) {
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(size);
        glBegin(GL_POINTS);
        glVertex2f(x, 500 - y);
        glEnd();
        glFlush();
    }
}

void keyboard_callback(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q')
        exit(1);
}

void menu(int id) {
    if (id == 1)
        exit(1);
    else if (id == 2)
        size *= 2;
    else
        size /= 2;
    glutPostRedisplay();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv) {
    glutInitWindowSize(500, 500);
    glutCreateWindow("1092923");
    glutDisplayFunc(mydisplay);

    glutMouseFunc(mouse_callback);
    glutKeyboardFunc(keyboard_callback);

    glutCreateMenu(menu);
    glutAddMenuEntry("quit", 1);
    glutAddMenuEntry("increase size", 2);
    glutAddMenuEntry("decrease size", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();

    glutMainLoop();
}