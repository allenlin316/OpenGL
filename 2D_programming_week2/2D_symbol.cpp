#include <GL/glut.h>

void mydisplay(){
     
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1.0, 0.0, 0.0);
	
     //glutWireTeapot(5.0);	 
	 glPointSize(10.0);
	
     // National Holiday symbol of Taiwan 
	 glBegin(GL_QUADS);
     
     glVertex2f(100, 200); // 橫的長方形
     glVertex2f(100, 250);
     glVertex2f(350, 250);
     glVertex2f(350, 200);

     
     glVertex2f(150, 150); // 直的長方形
     glVertex2f(150, 300);
     glVertex2f(200, 300);
     glVertex2f(200, 150);

     
     glVertex2f(250, 150); // 直的長方形
     glVertex2f(250, 300);
     glVertex2f(300, 300);
     glVertex2f(300, 150);


	 glEnd();

     glFlush();
}

void init()
{          
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0, 500, 0, 500, 0, 500);
	 glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv){
     glutInitWindowSize(500,500);
     glutCreateWindow("simple");
     glutDisplayFunc(mydisplay);

     init();

     glutMainLoop();
}