#include<stdio.h>
#include<GL/glut.h>
#include "ratio.h"
#include "main.h"
#define   mesh_maxx 20
#define   mesh_maxy 25
#define   mesh_dx 15
#define   mesh_dy 10
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

GLfloat mesh_x[mesh_maxx]={0.0},mesh_y[mesh_maxy]={0.0};
GLfloat mesh_x0=50.0,mesh_y0=50.0;
GLfloat mesh_screen[4]={-60,0,20,-40};

void mesh_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(mesh_screen[0],mesh_screen[3],mesh_screen[1],mesh_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void mesh()
{
	int i,j;
	glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
  	  polygon(mesh_screen[0],mesh_screen[1],mesh_screen[2],mesh_screen[3]);
	glPopMatrix();
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glLoadIdentity();
	glScaled(0.05,0.05,0.0);
	glTranslated(-1200.0,0.0,0.0);
	for(i=0;i<mesh_maxx;i++)
		mesh_x[i]=mesh_x0+i*mesh_dx;
	for(j=0;j<mesh_maxy;j++)
		mesh_y[j]=mesh_y0+j*mesh_dy;
	for(i=0;i<mesh_maxx-1;i++)
	    for(j=0;j<mesh_maxy-1;j++)
	    {
			glBegin(GL_LINE_LOOP);
			glVertex2f(mesh_x[i],mesh_y[j]);
        			glVertex2f(mesh_x[i],mesh_y[j+1]);
        			glVertex2f(mesh_x[i+1],mesh_y[j+1]);
			glVertex2f(mesh_x[i+1],mesh_y[j]);
        		glEnd();
        		glFlush();
		}
	glPopMatrix();
	glLoadIdentity();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(mesh_screen[0]+8,mesh_screen[1]-8);
	Write("Mesh",1);
}
