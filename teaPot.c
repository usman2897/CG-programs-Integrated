#include<GL/glut.h>
#include<stdio.h>
#include "ratio.h"
#include "main.h"
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

GLfloat tp_screen[4]={-60.0,70.0,90.0,-40.0};

void tp_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(tp_screen[0],tp_screen[3],tp_screen[1],tp_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void wall(double thickness)
{
	glPushMatrix();
		glTranslated(0.5,0.5*thickness,0.5);
		glScaled(1.0,thickness,1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}
void tableleg(double thick,double len)
{
   	glPushMatrix();
		glTranslated(0,len/2,0);
		glScaled(thick,len,thick);
		glutSolidCube(1.0);
	glPopMatrix();
}
void table(double topw,double topt,double legt,double legl)
{
	glPushMatrix();
		glTranslated(0,legl,0);
		glScaled(topw,topt,topw);
		glutSolidCube(1.0);
	glPopMatrix();

	double dist=0.95*topw/2.0-legt/2.0;

     	glPushMatrix();

     		glTranslated(dist,0,dist);
		tableleg(legt,legl);

   	 	glTranslated(0,0,-2*dist);
		tableleg(legt,legl);

    		glTranslated(-2*dist,0,2*dist);
		tableleg(legt,legl);

    		glTranslated(0,0,-2*dist);
		tableleg(legt,legl);
     	glPopMatrix();
   }
void teapot(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_SHADE_MODEL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	//GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
   	// GLfloat mat_diffuse[]={0.0f,0.5f,0.5f,1.0f};
    //	GLfloat mat_specular[]={0.0f,1.0f,1.0f,1.0f};
    //	GLfloat mat_shininess[]={100.0f};

 GLfloat lightamb[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
 GLfloat lightint[]  = { 1.0f, 1.0f, 1.0f, 1.0f };        /*Variables used for lighting and shading effects*/
 GLfloat lightspec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 GLfloat lightpos[] = { 2.0f, 5.0f, 5.0f, 0.0f };

 GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
 GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
 GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
 GLfloat mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	//GLfloat lightint[]={1.0f,1.0f,1.0f,1.0f};
	//GLfloat lightpos[]={320.0f,240.0f,3.0f,0.0f};
	//GLfloat lightamb[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
	//GLfloat lightspec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightint);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightamb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
	glColor3f(0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	polygon(tp_screen[0],tp_screen[1],tp_screen[2],tp_screen[3]);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glScaled(10.0,10.0,10.0);
	glTranslated(-5.0,7.8,0.0);
	glPushMatrix();
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
	glPushMatrix();
    	glRotated(90.0,0.0,0.0,1.0);
		wall(0.02);
    glPopMatrix();
  	wall(0.02);
    glPushMatrix();
   	 	glRotated(-90.0,1.0,0.0,0.0);
		wall(0.02);
	glPopMatrix();
	glPushMatrix();
        glTranslated(0.4,0,0.4);
		table(0.6,0.02,0.02,0.3);
	glPopMatrix();
    glPushMatrix();
		glTranslated(0.6,0.38,0.5);
		glRotated(30,0,1,0);
		glutSolidTeapot(0.08);
   	glPopMatrix();
   	glPopMatrix();
   	glPopMatrix();
   	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_SHADE_MODEL);
	glDisable(GL_NORMALIZE);
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(tp_screen[0]+7,tp_screen[1]-8);
	Write("TeaPot",1);
}
