#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#define COLOUMNS 30
#define ROW 30
#include "game.h"
#define FPS 10
extern short dir;
bool gameOver=false;

int score=0;
void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if(gameOver)
    {
        char s[10];
        itoa(score,s,10);
        char text[50]="YOUR SCORE: ";
        strcat(text,s);
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
    }
}
void reshape_callback(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLOUMNS,0.0,ROW,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    initGrid(COLOUMNS,ROW);
}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}
void keyboard_callback(int key,int,int)
{
     switch(key)
     {
     case GLUT_KEY_UP:
        if(dir!=DOWN)
            dir=UP;
        break;
     case GLUT_KEY_DOWN:
        if(dir!=UP)
            dir=DOWN;
        break;
     case GLUT_KEY_RIGHT:
        if(dir!=LEFT)
            dir=RIGHT;
        break;
     case GLUT_KEY_LEFT:
        if(dir!=RIGHT)
            dir=LEFT;
        break;
     }
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(500,150);
    glutInitWindowSize(500,500);

    glutCreateWindow("Snake Game");

    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(keyboard_callback);
    init();

    glutMainLoop();
}
