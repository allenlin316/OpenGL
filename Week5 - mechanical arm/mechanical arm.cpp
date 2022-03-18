#include <GL/glut.h>
#include <math.h>

int angle = 1;
GLUquadricObj* q;

void base() {
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    //gluQuadricDrawStyle(q, GLU_LINE);
    gluCylinder(q, 5, 5, 5, 20, 1);
    glPopMatrix();
}

void lower_arm() {
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0);
    glRotatef(-30, 1, -1, 1);
    glTranslatef(0, 2, 0);
    glScalef(0.3, 1.5, 0.3);
    glutSolidCube(5);
    glPopMatrix();
}

void upper_arm() {
    glPushMatrix();
    glColor3f(0.3, 0.0, 0.5);
    glTranslatef(2.5, 5.8, -1);
    glRotatef(-170, 1, -1, 1);
    //glTranslatef(-5, -1, 0);
    glScalef(0.3, 1, 0.3);
    glutSolidCube(5);
    glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
        case 'Z':
            angle = 0;
            angle += 1;
            break;
        case 'x':
        case 'X':
            angle = 0;
            angle -= 1;
            break;
        case 'q':
        case 'Q':
            exit(1);
            break;
    }
    glutPostRedisplay();
}

void mydisplay() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    glPushMatrix();
    base();
    lower_arm();
    upper_arm();
    glPopMatrix();
    glRotatef(angle, 0, 0, 1);

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
    gluLookAt(0, 1, 0.5, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    q = gluNewQuadric();
}

void main(int argc, char** argv) {
    glutInitWindowSize(500, 500);
    glutCreateWindow("1092923 ªL«~¦w");
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
}