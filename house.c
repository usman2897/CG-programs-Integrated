#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include "ratio.h"
#include "main.h"
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

GLfloat house[3][9]={ {10.0,10.0,17.5,25.0,25.0,15.0,15.0,20.0,20.0},
	       	           {10.0,30.0,40.0,30.0,10.0,10.0,15.0,15.0,10.0},
	                         {1.0,   1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0  }  };
GLfloat house_theta=0.0;
GLfloat house_rot_mat[3][3]={{0},{0},{0}};
GLfloat house_result[3][9]={{0},{0},{0}};
GLfloat h=10.0;
GLfloat k=10.0;
GLfloat house_screen[4]={-90,35,55,-70};

void multiply()
{
	int i,j,l;
	for(i=0;i<3;i++)
	for(j=0;j<9;j++)
	     {
	       house_result[i][j]=0;
	       for(l=0;l<3;l++)
				house_result[i][j]=house_result[i][j]+house_rot_mat[i][l]*house[l][j];
	       }
}
void house_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(house_screen[0],house_screen[3],house_screen[1],house_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void rotate()
{
	GLfloat m,n;
	m=-h*(cos(house_theta)-1)+k*(sin(house_theta));
	n=-k*(cos(house_theta)-1)-h*(sin(house_theta));
	house_rot_mat[0][0]=cos(house_theta);
	house_rot_mat[0][1]=-sin(house_theta);
	house_rot_mat[0][2]=m;
	house_rot_mat[1][0]=sin(house_theta);
	house_rot_mat[1][1]=cos(house_theta);
	house_rot_mat[1][2]=n;
	house_rot_mat[2][0]=0;
	house_rot_mat[2][1]=0;
	house_rot_mat[2][2]=1;
	multiply();
}
void drawrotatedhouse()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house_result[0][0],house_result[1][0]);
	glVertex2f(house_result[0][1],house_result[1][1]);
	glVertex2f(house_result[0][3],house_result[1][3]);
	glVertex2f(house_result[0][4],house_result[1][4]);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house_result[0][5],house_result[1][5]);
	glVertex2f(house_result[0][6],house_result[1][6]);
	glVertex2f(house_result[0][7],house_result[1][7]);
	glVertex2f(house_result[0][8],house_result[1][8]);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house_result[0][1],house_result[1][1]);
	glVertex2f(house_result[0][2],house_result[1][2]);
	glVertex2f(house_result[0][3],house_result[1][3]);
	glEnd();
}
void draw_house()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][0],house[1][0]);
	glVertex2f(house[0][1],house[1][1]);
	glVertex2f(house[0][3],house[1][3]);
	glVertex2f(house[0][4],house[1][4]);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][5],house[1][5]);
	glVertex2f(house[0][6],house[1][6]);
	glVertex2f(house[0][7],house[1][7]);
	glVertex2f(house[0][8],house[1][8]);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][1],house[1][1]);
	glVertex2f(house[0][2],house[1][2]);
	glVertex2f(house[0][3],house[1][3]);
	glEnd();
}
void home()
{
	glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	polygon(house_screen[0],house_screen[1],house_screen[2],house_screen[3]);
	glPopMatrix();
	glLoadIdentity();
	glScaled(0.3,0.3,0.0);
	glTranslated(-275.0,139.0,0.0);
	draw_house();
	glPushMatrix();
	  rotate();
	  drawrotatedhouse();
	glPopMatrix();
	glLoadIdentity();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(house_screen[0]+4,house_screen[1]-8);
	Write("Rotate House",1);
}
