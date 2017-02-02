#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

int count=0;
GLfloat orthoCo[4]={-100.0,-100.0,100.0,60.0};
int width=800,height=600,m;
float xratio;
float yratio;

void cal_ratio(GLfloat y[])
{
	xratio=width/(y[3]-y[0]);
	yratio=height/(y[2]-y[1]);
}
void Write(char *string,int size)
{
	if(size==1)
	{
		while(*string){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*string++);}
	}
	else if(size==2)
    {
		while(*string){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
		}
	}
}
void myinit()
{
	glClearColor(1.0,0.7,0.5,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(orthoCo[0],orthoCo[3],orthoCo[1],orthoCo[2],-100.0,100.0);
}
void polygon(GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
	glBegin(GL_POLYGON);
	  glVertex3f(a,b,-99.0);
	  glVertex3f(a,c,-99.0);
	  glVertex3f(d,c,-99.0);
	  glVertex3f(d,b,-99.0);
	glEnd();
}

void display()
{
	if(count==0){
		myinit();count++;
		cal_ratio(orthoCo);
	}
	cube();
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	teapot();
	tetrahedron(tet_n);
	home();
	liangBarsky();
	cohenSutherland();
	cylPara();
	mesh();
	polyfill();
	ccube();
	createIcon();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(-40,-40);
	Write("BY",2);
	glRasterPos2f(-20,-50);
	Write("MOHAMMED USMAN",2);
	glRasterPos2f(-20,-60);
	Write("14GAEC9025",2);
	glRasterPos2f(-20,-70);
	Write("5th Sem CSE",2);
	glRasterPos2f(-20,-80);
	Write("Under the Guidance of VIMALA Ma'am",2);
	count++;
	if(count>30000)count=1;
	glFlush();
	glutSwapBuffers();
}

void animation(float screen[])
{
	int i,j,k,l; i=orthoCo[0]-screen[0];j=orthoCo[3]-screen[3];k=orthoCo[1]-screen[1];l=orthoCo[2]-screen[2];
	float inci=(float)i/(float)10,incj=(float)j/(float)10,inck=(float)k/(float)10,incl=(float)l/(float)10,inc;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	for(inc=0;inc<=10;inc++)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(orthoCo[0]-inci*inc,orthoCo[3]-incj*inc,orthoCo[1]-inck*inc,orthoCo[2]-incl*inc,-100.0,100.0);
		display();
	}
}
void mouse(int button,int status,int x,int y)
{
	y=height-y;
	if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(cube_screen[0]-orthoCo[0])&&x<=xratio*(cube_screen[3]-orthoCo[0]))&&(y>=yratio*(cube_screen[1]-orthoCo[1])&&y<=yratio*(cube_screen[2]-orthoCo[1])))
	{
		animation(cube_screen);
		glutMouseFunc(cube_mouse);
		glutReshapeFunc(cube_myReshape);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(tp_screen[0]-orthoCo[0])&&x<=xratio*(tp_screen[3]-orthoCo[0]))&&(y>=yratio*(tp_screen[1]-orthoCo[1])&&y<=yratio*(tp_screen[2]-orthoCo[1])))
	{
		animation(tp_screen);
		glutMouseFunc(0);
		glutReshapeFunc(tp_myReshape);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(tet_screen[0]-orthoCo[0])&&x<=xratio*(tet_screen[3]-orthoCo[0]))&&(y>=yratio*(tet_screen[1]-orthoCo[1])&&y<=yratio*(tet_screen[2]-orthoCo[1])))
	{
		animation(tet_screen);
		glutMouseFunc(0);
		glutReshapeFunc(tet_myReshape);
		printf("Enter the No. of Recursions of Tetrahedron: ");
		scanf("%d",&tet_n);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(house_screen[0]-orthoCo[0])&&x<=xratio*(house_screen[3]-orthoCo[0]))&&(y>=yratio*(house_screen[1]-orthoCo[1])&&y<=yratio*(house_screen[2]-orthoCo[1])))
	{
		animation(house_screen);
		glutMouseFunc(0);
		glutReshapeFunc(house_myReshape);
		printf("Enter the angle to rotate the house by: ");
		scanf("%f",&house_theta);
		house_theta=house_theta*3.14/180;
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(lb_screen[0]-orthoCo[0])&&x<=xratio*(lb_screen[3]-orthoCo[0]))&&(y>=yratio*(lb_screen[1]-orthoCo[1])&&y<=yratio*(lb_screen[2]-orthoCo[1])))
	{
		animation(lb_screen);
		glutReshapeFunc(lb_myReshape);
		glutMouseFunc(0);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(cohen_screen[0]-orthoCo[0])&&x<=xratio*(cohen_screen[3]-orthoCo[0]))&&(y>=yratio*(cohen_screen[1]-orthoCo[1])&&y<=yratio*(cohen_screen[2]-orthoCo[1])))
	{
		animation(cohen_screen);
		glutReshapeFunc(cohen_myReshape);
		glutMouseFunc(0);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(parcyl_screen[0]-orthoCo[0])&&x<=xratio*(parcyl_screen[3]-orthoCo[0]))&&(y>=yratio*(parcyl_screen[1]-orthoCo[1])&&y<=yratio*(parcyl_screen[2]-orthoCo[1])))
	{
		animation(parcyl_screen);
		glutReshapeFunc(parcyl_myReshape);
		glutMouseFunc(0);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(mesh_screen[0]-orthoCo[0])&&x<=xratio*(mesh_screen[3]-orthoCo[0]))&&(y>=yratio*(mesh_screen[1]-orthoCo[1])&&y<=yratio*(mesh_screen[2]-orthoCo[1])))
	{
		animation(mesh_screen);
		glutReshapeFunc(mesh_myReshape);
		glutMouseFunc(0);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(sf_screen[0]-orthoCo[0])&&x<=xratio*(sf_screen[3]-orthoCo[0]))&&(y>=yratio*(sf_screen[1]-orthoCo[1])&&y<=yratio*(sf_screen[2]-orthoCo[1])))
	{
		animation(sf_screen);
		glutReshapeFunc(sf_myReshape);
		glutMouseFunc(0);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=xratio*(cbv_screen[0]-orthoCo[0])&&x<=xratio*(cbv_screen[3]-orthoCo[0]))&&(y>=yratio*(cbv_screen[1]-orthoCo[1])&&y<=yratio*(cbv_screen[2]-orthoCo[1])))
	{
		animation(cbv_screen);
		glutMouseFunc(ccube_mouse);
		glutReshapeFunc(cbv_myReshape);
		glutKeyboardFunc(ccube_keys);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x/xratio+orthoCo[0]>=8.4&&x/xratio+orthoCo[0]<=45&&y/yratio+orthoCo[1]>=30.0&&y/yratio+orthoCo[1]<=61.33))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective (60, (GLfloat)width / (GLfloat)height, 10, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glutDisplayFunc(avl_display);
		glutKeyboardFunc(avl_keyboard);
		glutReshapeFunc(avl_myReshape);
		glutMouseFunc(0);
		glutIdleFunc(0);
		count=0;
		glutPostRedisplay();
	}
}
void keyboard(unsigned char c,int x,int y)
{
	if(c=='b')
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(orthoCo[0],orthoCo[3],orthoCo[1],orthoCo[2],-100.0,100.0);
		glutMouseFunc(mouse);
		glutReshapeFunc(myReshape);
	}
	else if(c=='q') exit(0);
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(orthoCo[0],orthoCo[3],orthoCo[1],orthoCo[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void idle()
{
	cube_spin();
}
int main(int argc,char **argv)
{
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
		glutInitWindowPosition(10,20);
		glutInitWindowSize(width,height);
		glutCreateWindow("Computer Graphics Project!");
		glutReshapeFunc(myReshape);
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
        glutIdleFunc(idle);
        glutKeyboardFunc(keyboard);
		glEnable(GL_DEPTH_TEST);
		glColor3f(1.0,1.0,1.0);
		glutMainLoop();
}
