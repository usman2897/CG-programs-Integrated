#include<stdio.h>
#include<GL/glut.h>
#include "ratio.h"
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);
GLfloat sf_screen[4]={-30,0,20,-10};

void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
float mx,x,temp;
int i;
	if((y2-y1)<0)
	{
		temp=y1;y1=y2;y2=temp;
		temp=x1;x1=x2;x2=temp;
	}
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
		mx=x2-x1;
	x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
			le[i]=(int)x;
		if(x>(float)re[i])
			re[i]=(int)x;
		x+=mx;
	}
}
void s_draw_pixel(int x,int y)
{
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	int le[500],re[500];
	int i,y;
	for(i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x1,y1,le,re);
	for(y=0;y<500;y++)
	{
		if(le[y]<=re[y])
			for(i=(int)le[y];i<(int)re[y];i++)
				s_draw_pixel(i,y);

	}

}
void sf_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(sf_screen[0],sf_screen[3],sf_screen[1],sf_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void polyfill()
{
	float x1,x2,x3,x4,y1,y2,y3,y4;
x1=200.0;y1=200.0;x2=100.0;y2=300.0;x3=200.0;y3=400.0;x4=300.0;y4=300.0;
glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
  	  polygon(sf_screen[0],sf_screen[1],sf_screen[2],sf_screen[3]);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glScaled(0.05,0.05,0.0);
	glTranslated(-600,-100,0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
  glVertex2f(x1,y1);
  glVertex2f(x2,y2);
  glVertex2f(x3,y3);
  glVertex2f(x4,y4);
  glEnd();
  scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
  glPopMatrix();
  glLoadIdentity();
  glColor3f(0.0,0.0,1.0);
	glRasterPos2f(sf_screen[0]+3,sf_screen[1]-8);
	Write("ScanfillAlgorithm",1);
}
