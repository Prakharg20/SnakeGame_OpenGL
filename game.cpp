#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"
#include<ctime>
int gridX,gridY;
extern int score;
int snake_length=5;
bool food=true;
int foodX,foodY;
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
short dir=RIGHT;
extern bool gameOver;
void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;
}
void unit(int x,int y)
{
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }
    glBegin(GL_LINE_LOOP);
     glVertex2f(x,y);
     glVertex2f(x+1,y);
     glVertex2f(x+1,y+1);
    glVertex2f(x,y+1);
    glEnd();
}
void drawGrid()
{
    for(int i=0;i<gridX;i++)
    {
        for(int j=0;j<gridY;j++)
        {
            unit(i,j);
        }
    }
}
void random(int &x,int &y)
{
    srand(time(NULL));
    int maxX=gridX-2;
    int maxY=gridY-2;
    int m=1;
    x=m+rand()%(maxX-m);
    y=m+rand() %(maxY-m);

}
void drawFood()
{
    if(food)
        random(foodX,foodY);
    food=false;
    glColor3f(1.0,0.0,0.0);
    glRectd(foodX,foodY,foodX+1,foodY+1);
}
void drawSnake()
{
    for(int i=snake_length-1;i>0;i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(dir==UP)
        posY[0]++;
    else if(dir==DOWN)
        posY[0]--;
    else if(dir==LEFT)
        posX[0]--;
    else if(dir==RIGHT)
        posX[0]++;
    for(int i=0;i<snake_length;i++)
    {
        if(i==0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.0,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    for(int j=1;j<snake_length;j++)
{
        if(posX[j]==posX[0] && posY[j]==posY[0])
            gameOver=true;
}

    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==gridY-1 || posY[0]==0)
        gameOver=true;
    if(posX[0]==foodX && posY[0]==foodY)
    {
        score++;
        snake_length++;
        if(snake_length>MAX)
            snake_length=MAX;
        food=true;

    }
}

