/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * 
 *
 * To compile this project you must include the following libraries:
 * opengl32.lib,glu32.lib,glut.lib
 * You need also the header file glut.h in your compiler directory.
 *  
 */

/*
 * 3DS Spaceship created by: Rene Reiter <renereiter@hotmail.com>
 */



#include <windows.h>
#include <string>
#include <math.h>
#include <fstream>
#include <time.h>
#include <GL/glut.h>
#include "tutorial4.h"
#include "texture.h"
#include "3dsloader.h"
#define MAX_CHAR     128



/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// render background
obj2_type object2 = {
    {
        -1, 1,
        -1, -1,
        1, -1,
        1, 1
    },
    {
        0, 1, 2,
        0, 2, 3
    },
    {
        0.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0
    },
    0,
};

bool gameStartCheck = false, isReset = false;
int counter = 30;
int drop_speed1 =200, drop_speed2 = 200, drop_speed3 = 200, drop_speed4 = 200;
int barrier_x1=rand()%150, barrier_x2=rand()%150, barrier_x3=rand()%150, barrier_x4=rand()%150;
int life = 50;
char life_text[10], buffer[10];
char buffer_timer[3], timer_title[]="Time: ";


// The width and height of your window, change them as you like
int screen_width=500;
int screen_height=500;

double distance_x = 0, distance_x_increment = 5;
double distance_y = -100, distance_y_increment = 5;
double distance_z = -500, distance_z_increment = 3;
// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

//Now the object is generic, the cube has annoyed us a little bit, or not?
obj_type object;

void setBackground() {
    int l_index;

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue            
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity    
    glTranslatef(0, 0, distance_z);
    //glEnable(GL_DEPTH_TEST);   

    ////導入紋理(載入照片)    
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(200, 200, 0);
    glTranslatef(0, 0, distance_z - 500);
    glBindTexture(GL_TEXTURE_2D, object2.id_texture); // We set the active texture 

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index = 0; l_index < 2; l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f(object2.mapcoord[object2.polygon[l_index].a].u,
            object2.mapcoord[object2.polygon[l_index].a].v);
        // Coordinates of the first vertex
        glVertex2f(object2.vertex[object2.polygon[l_index].a].x,
            object2.vertex[object2.polygon[l_index].a].y); //Vertex definition

//----------------- SECOND VERTEX -----------------
// Texture coordinates of the second vertex
        glTexCoord2f(object2.mapcoord[object2.polygon[l_index].b].u,
            object2.mapcoord[object2.polygon[l_index].b].v);
        // Coordinates of the second vertex
        glVertex2f(object2.vertex[object2.polygon[l_index].b].x,
            object2.vertex[object2.polygon[l_index].b].y);

        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f(object2.mapcoord[object2.polygon[l_index].c].u,
            object2.mapcoord[object2.polygon[l_index].c].v);
        // Coordinates of the Third vertex
        glVertex2f(object2.vertex[object2.polygon[l_index].c].x,
            object2.vertex[object2.polygon[l_index].c].y);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    /////////////////    
}

// set text on screen
void drawText(const char* text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}


void init(void)
{
    srand(time(NULL));
    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
   	
    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"
   
    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
    
    //glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    Load3DS (&object,"spaceship.3ds");

    object.id_texture=LoadBitmap("spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID
    object2.id_texture = LoadBitmap("background.bmp");
    
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture==-1)
    {
        MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }
}

void resize (int width, int height)
{
    screen_width=width; // We obtain the new screen width values and store it
    screen_height=height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

void welcomeDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       
    glColor3f(1, 1, 1);    
    std::string text = "==Welcome to Spaceship Game==";
    drawText(text.data(), text.size(), 130, 400);
    text = "press SPACE to play";
    drawText(text.data(), text.size(), 230, 350);
    setBackground(); // set space image in the background

    glFlush();
    glutSwapBuffers();
}

void reset() {
    // reset the game page whenever ship is hit
    drop_speed1 = drop_speed2 = drop_speed3 = drop_speed4 = 200;
    distance_x = 0;
    distance_y = -100;
}

void gameOver() {       
    gameStartCheck = false;    
    std::string text = "Game Over!";
    drawText(text.data(), text.size(), 280, 400);
    text = "press SPACE to play again!";
    drawText(text.data(), text.size(), 180, 350);
    setBackground();    
    glFlush();
    glutSwapBuffers();
    isReset = true; // in order to render last time of display()
}

void judgeGameStatus() {
    if (abs(distance_x - barrier_x1) < 30 && abs(distance_y - drop_speed1) < 30) {
        printf("hit with barrier1\n");
        life -= 10;
        reset();
    }
    if (abs(distance_x - barrier_x2) < 30 && abs(distance_y - drop_speed2) < 30) {
        printf("hit with barrier2\n");
        life -= 10;
        reset();
    }
    if (abs(distance_x - barrier_x3) < 30 && abs(distance_y - drop_speed3) < 30) {
        printf("hit with barrier3\n");
        life -= 10;
        reset();
    }
    if (abs(distance_x - barrier_x4) < 30 && abs(distance_y - drop_speed4) < 30) {
        printf("hit with barrier4\n");
        life -= 10;
        reset();
    }
    if (life <= 0) {     
        if (isReset) {
            glutIdleFunc(NULL);
            glutPostRedisplay();
        }
        reset();
        glutDisplayFunc(gameOver);                       
    }
}

// count down timer of the game
void timer(int t) {
    if (counter <= 0) {        
        gameStartCheck = false;
        glutIdleFunc(NULL);
        glutDisplayFunc(gameOver);
        glutPostRedisplay();      
    }
    if (gameStartCheck) {
        glutTimerFunc(1000, timer, 0);
        counter--;
        printf("counter: %d\n", counter);
        glutPostRedisplay();
    }
}

void display(void)
{
    int l_index;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue            
    setBackground(); // set space view in the background       
                     
     // obstacles coming from above
    glPushMatrix();
    if (drop_speed1 <= -200) {
        drop_speed1 = 200;
        barrier_x1 = rand() % 150-150;
    }
    glTranslatef(barrier_x1, drop_speed1-=3, 100);
    glScalef(5, 20, 0);
    glutSolidCube(3);
    glPopMatrix();

    // obstacles coming from above
    glPushMatrix();
    if (drop_speed2 <= -200) {
        drop_speed2 = 200;
        barrier_x2 = rand() % 150-150;
    }
    glTranslatef(barrier_x2, drop_speed2-=2, 100);
    glScalef(5, 20, 0);
    glutSolidCube(3);
    glPopMatrix();

    // obstacles coming from above
    glPushMatrix();
    if (drop_speed3 <= -200) {
        drop_speed3 = 200;
        barrier_x3 = rand() % 150-150;
    }
    glTranslatef(barrier_x3, drop_speed3--, 100);
    glScalef(5, 20, 0);
    glutSolidCube(3);
    glPopMatrix();

    // obstacles coming from above
    glPushMatrix();
    if (drop_speed4 <= -200) {
        drop_speed4 = 200;
        barrier_x4 = rand()%150-150;
    }
    glTranslatef(barrier_x4, drop_speed4--, 100);
    glScalef(5, 20, 0);
    glutSolidCube(3);
    glPopMatrix();
    
    glTranslatef(distance_x, distance_y, 100); // We move the object forward (the model matrix is multiplied by the translation matrix)      
    //printf("distance_x: %f, distance_y: %f\n", distance_x, distance_y);
    glRotatef(180,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
    glRotatef(180,0.0,1.0,0.0);
    glRotatef(0,0.0,0.0,1.0);
    glScalef(0.25, 0.25, 0.25);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<object.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                      object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();    
    glDisable(GL_TEXTURE_2D);

    memset(timer_title, 0, sizeof(timer_title));
    strcpy(timer_title, "Time: ");
    memset(buffer_timer, 0, sizeof(buffer_timer));
    itoa(counter, buffer_timer, 10);
    strcat(timer_title, buffer_timer);
    drawText(timer_title, strlen(timer_title), 5, 550);

    memset(buffer, 0, sizeof(buffer));
    strcpy(life_text, "Life: ");
    strcat(life_text, itoa(life, buffer, 10));
    drawText(life_text, strlen(life_text), 5, 500);

    // judge whether hit the barriers
    judgeGameStatus();


    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}

void gameStart() {
    gameStartCheck = true;
    isReset = false;
    life = 50;
    counter = 30;
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(1000, timer, 0);
    printf("gameStartCheck: %d", gameStartCheck);
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'w': case 'W':
        distance_y += distance_y_increment;
        break;
    case 's': case 'S':
        distance_y -= distance_y_increment;
        break;
    case 'a': case 'A':
        distance_x -= distance_x_increment;
        break;
    case 'd': case 'D':
        distance_x += distance_x_increment;
        break;
    case 'r': case 'R':
        if (filling == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
            filling = 1;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
            filling = 0;
        }
        break;
    case ' ':
        gameStart();
        break;
    }
    glutPostRedisplay();
}

void keyboard_s(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_UP:
        distance_y += distance_y_increment;
        break;
    case GLUT_KEY_DOWN:
        distance_y -= distance_y_increment;
        break;
    case GLUT_KEY_LEFT:
        distance_x -= distance_x_increment;
        break;
    case GLUT_KEY_RIGHT:
        distance_x += distance_x_increment;
        break;
    }
    glutPostRedisplay();
}
/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("www.spacesimulator.net - 3d engine tutorials: Tutorial 4");    
    glutDisplayFunc(welcomeDisplay);   
    //glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
