#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846

float angle = 0;
float theta = 0;

void setOrbitAndPlanet(float x, float z, float planet_size, float rotate_speed, GLubyte red, GLubyte green, GLubyte blue) {
    // set the orbit
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        glColor3d(1, 1, 1);
        theta = i * PI / 180;
        float radius = sqrt(x * x + z * z);
        glVertex3f(radius * cos(theta), 0, radius * sin(theta));
    }
    glEnd();

    // set the position of the planet and rotate 
    glPushMatrix();
        glColor3ub(red, green, blue);
        glRotatef(angle*rotate_speed, 0, 1, 0);
        glTranslatef(x, 0, z);
        glRotatef(angle * rotate_speed, 0, 1, 0);
        glutSolidSphere(planet_size, 20, 20);
    glPopMatrix();
}

void mydisplay(){
     
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     // sun
     glPushMatrix();
         glColor3d(1, 0, 0);
         glRotatef(angle, 0, 0, 1);
         glutSolidSphere(2.5, 20, 20);
     glPopMatrix();

     setOrbitAndPlanet(4, 4, 0.5, 2.5, 0, 255, 255);       //水星(Mercury)
     setOrbitAndPlanet(6, 6, 1.3, 2, 255, 215, 0);   // 金星(Venus)
     setOrbitAndPlanet(8, 8, 1.5, 1, 0, 0, 215);         // 地球(Earth)
     setOrbitAndPlanet(10, 10, 1, 1.5, 215, 95, 0);    //  火星(Mars)
     setOrbitAndPlanet(12, 12, 2.5, 0.5, 200, 175, 95);    //  木星(Jupiter)
     setOrbitAndPlanet(14, 14, 2, 0.4, 215, 215, 0); //  土星(Saturn)
     setOrbitAndPlanet(16, 16, 1.8, 0.3, 135, 215, 255); //  天王星(Uranus)
     setOrbitAndPlanet(18, 18, 1.9, 0.1, 135, 175, 255);    //  海王星(Neptune)

     glFlush();
}

void rotate() {
    angle += 0.1;
    //if (angle > 1800) angle = 0;
    glutPostRedisplay();
}

void init()
{          
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
     gluLookAt(0, -0.5, 1, 0, 0, 0, 0, 1, 0);
	 glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv){
     glutInitWindowSize(500,500);
     glutCreateWindow("solar-system");
     glutDisplayFunc(mydisplay);
     glutIdleFunc(rotate);

     init();

     glutMainLoop();
}