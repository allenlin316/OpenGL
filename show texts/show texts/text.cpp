#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

#define MAX_CHAR       128

void drawString(const char* str) {

    static int isFirstCall = 1;
    static GLuint lists;

    if (isFirstCall) { // 如果是第一次調用，執行初始化

// 爲每一個ASCII字符產生一個顯示列表

        isFirstCall = 0;

        // 申請MAX_CHAR個連續的顯示列表編號

        lists = glGenLists(MAX_CHAR);

        // 把每個字符的繪製命令都裝到對應的顯示列表中

        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);

    }

    // 調用每個字符對應的顯示列表，繪製每個字符

    for (; *str != '\0'; ++str)
        glCallList(lists + *str);

}



void selectFont(int size, int charset, const char* face) {

    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,

        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,

        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);

    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);

    DeleteObject(hOldFont);

}



void display(void) {

    selectFont(48, ANSI_CHARSET, "Comic Sans MS");

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(0.0f, 0.0f);

    drawString("Hello, World!");

    glutSwapBuffers();

}



void init(void)

{
    glClearColor(0.0, 0.0, 0.0, 0.0); /* select clearing olor  */

    //  glMatrixMode(GL_PROJECTION); /* initialize viewing values  */
    //  glLoadIdentity();
    //  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //注意該視景體的範圍和幾何中心

}





int main(int argc, char** argv)

{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  //改爲glutInitWindowSize (250, 250); 可以看出變換的僅僅是物體按比例大小的變換
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Text");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}