#include<stdio.h>
#include<GL/glut.h>
#include "ratio.h"
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

//main
void myReshape(int,int);
void keyboard(unsigned char c,int x,int y);
void mouse(int button,int status,int x,int y);
extern GLfloat orthoCo[];

//cube
extern GLfloat    cube_vertices[];
extern GLfloat cube_normals[];
extern GLfloat     cube_colors[];
extern GLubyte cube_Indices[];

GLfloat camera_theta[3]={0.0,0.0,0.0};
GLint camera_axis=2;
static GLdouble viewer[]={0.0,0.0,5.0};
GLfloat cbv_screen[4]={-90.0,-35.0,-15.0,-70.0};

void ccube_mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)camera_axis=0;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) camera_axis=1;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) camera_axis=2;
	camera_theta[camera_axis]+=2.0;
	if(camera_theta[camera_axis]>360.0)
		camera_theta[camera_axis]-=360.0;
	glutPostRedisplay();
}
void ccube_keys(unsigned char key, int x, int y)
{
		if(key=='x')   viewer[0]-=1.0;
		if(key=='X')  viewer[0]+=1.0;
		if(key=='y')   viewer[1]-=1.0;
		if(key=='Y')  viewer[1]+=1.0;
		if(key=='z')   viewer[2]-=1.0;
		if(key=='Z')  viewer[2]+=1.0;
		if(key=='b')
		{
			glutMouseFunc(mouse);
			glutReshapeFunc(myReshape);
			glutKeyboardFunc(keyboard);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(orthoCo[0],orthoCo[3],orthoCo[1],orthoCo[2],-100.0,100.0);
		}
		glutPostRedisplay();
}
void cbv_myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	glFrustum(cbv_screen[0],cbv_screen[3],cbv_screen[1],cbv_screen[2],-1000.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
	width=w;height=h;cal_ratio(orthoCo);
}
void ccube()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,cube_vertices);
	glColorPointer(3,GL_FLOAT,0,cube_colors);
	glNormalPointer(GL_FLOAT,0,cube_normals);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glLoadIdentity();
	polygon(cbv_screen[0],cbv_screen[1],cbv_screen[2],cbv_screen[3]);
	glPopMatrix();
	glLoadIdentity();
	glPushMatrix();
	glScaled(5.0,5.0,5.0);
	glTranslated(-16.0,-5.0,0.0);
	glPushMatrix();
	gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,1.0,0.0);
	glRotatef(camera_theta[0],1.0,0.0,0.0);
	glRotatef(camera_theta[1],0.0,1.0,0.0);
	glRotatef(camera_theta[2],0.0,0.0,1.0);
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cube_Indices);
	glPopMatrix();
	glPopMatrix();
	glLoadIdentity();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(cbv_screen[0]+5,cbv_screen[1]-8);
	Write("ViewsOfCube",1);
}
