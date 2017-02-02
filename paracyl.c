#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include "ratio.h"
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

int cyl_n=50,par_n=40;
GLfloat parcyl_screen[4]={-90,0,20,-70};

void draw_pixel(GLint cx,GLint cy)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(cx,cy);
	glEnd();
}
void plot_pixel(GLint h,GLint k,GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}
void circle_draw(GLint h,GLint k,GLint r)
{
	GLint d=1-r,x=0,y=r;
	while(y>x)
	        {
	          plot_pixel(h,k,x,y);
	          if(d<0)  d+=2*x+3;
	          else
		{
		  d+=2*(x-y)+5;
		  --y;
		 } ++x;
	          }
	plot_pixel(h,k,x,y);
}
void cylinder_draw()
{
	GLint xc=100,yc=100,r=50;
	GLint i;
	for(i=0;i<cyl_n;i+=3)
	      circle_draw(xc,yc+i,r);
}
void parcyl_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(parcyl_screen[0],parcyl_screen[3],parcyl_screen[1],parcyl_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void parallelopiped(int x1,int x2,int y1,int y2,int y3,int y4)
{
	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y3);
		glVertex2f(x2,y4);
		glVertex2f(x1,y2);
	glEnd();
}
void parallelopiped_draw()
{
	int x1=200,x2=300,y1=100,y2=175,y3=100,y4=175;
	GLint i;
	for(i=0;i<par_n;i+=2)
	     parallelopiped(x1+i,x2+i,y1+i,y2+i,y3+i,y4+i);
}
void cylPara()
{
	glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
  	  polygon(parcyl_screen[0],parcyl_screen[1],parcyl_screen[2],parcyl_screen[3]);
	glPopMatrix();
	glPushMatrix();
	  glLoadIdentity();
	  glScaled(0.05,0.05,0.0);
	  glTranslated(-1800.0,50.0,0.0);
	  glPointSize(2.0);
	  cylinder_draw();
	  parallelopiped_draw();
	glPopMatrix();
	glLoadIdentity();
	  glColor3f(0.0,0.0,1.0);
	  glRasterPos2f(parcyl_screen[0]+1,parcyl_screen[1]-8);
	  Write("CylinderParallelopiped",1);
	
}
