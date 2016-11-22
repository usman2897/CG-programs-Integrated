#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define true 1
#define false 0
#define outcode int

void myReshape(int,int);
outcode ComputeOutCode (double x, double y);
void keyboard(unsigned char c,int x,int y);
void mouse(int button,int status,int x,int y);


//tetrahedron
void tetrahedron(int );
void  tet_myReshape(int w,int h);

//cube_data
void cube_mouse(int btn,int state,int x,int y);
void cube_spin();
void cube_myReshape(int w,int h);
void cube(void);

//tetrahedron
extern int tet_n;

//house
extern GLfloat house_theta;

//liangBarsky
//CohenSutherland
//Cylinder_Parallelopiped
//mesh_data
//Viewing a cube
void ccube_mouse(int btn, int state, int x, int y);
void ccube_keys(unsigned char key, int x, int y);
void ccube_myReshape(int w, int h);
void ccube();
int count=0;
GLfloat orthoCo[6]={-100.0,100.0,-100.0,100.0,-100.0,100.0};
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
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(orthoCo[0],orthoCo[1],orthoCo[2],orthoCo[3],orthoCo[4],orthoCo[5]);
}
void polygon(GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
	glBegin(GL_POLYGON);
	  glVertex3f(a,b,-100.0);
	  glVertex3f(a,c,-100.0);
	  glVertex3f(d,c,-100.0);
	  glVertex3f(d,b,-100.0);
	glEnd();
}

//cube
//teapot
//tetrahedron
//house
//LiangBarsky
//CYlinder & Parallelopiped
//mesh
//scanfill
//viewing a cube

void display()
{
	if(count==0){
		myinit();count++;
	}
	cube();
	teapot();
	tetrahedron(tet_n);
	home();
	liangBarsky();
	cohenSutherland();
	cylPara();
	mesh();
	polyfill();
	ccube();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(-10,-40);
	Write("BY",2);
	glRasterPos2f(0,-50);
	Write("MOHAMMED USMAN",2);
	glRasterPos2f(0,-60);
	Write("14GAEC9025",2);
	glRasterPos2f(0,-70);
	Write("5th Sem CSE",2);
	glRasterPos2f(0,-80);
	Write("Under the Guidance of Vimala Mam",2);
	glFlush();
	glutSwapBuffers();
}


void mouse(int button,int status,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&(x>=40&&x<=120)&&(y>=30&&y<=90))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-90.0,-70.0,70.0,90.0,-100.0,100.0);
		glutMouseFunc(cube_mouse);
		glutReshapeFunc(cube_myReshape);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=160&&x<=240)&&(y>=30&&y<=90))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-60.0,-40.0,70.0,90.0,-100.0,100.0);
		glutMouseFunc(0);
		glutReshapeFunc(tet_myReshape);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=280&&x<=360)&&(y>=30&&y<=90))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0,-10.0,70.0,90.0,-100.0,100.0);
		glutMouseFunc(0);
		scanf("%d",&tet_n);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=40&&x<=120)&&(y>=135&&y<=195))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-90.0,-70.0,35.0,55.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
		scanf("%f",&house_theta);
		house_theta=house_theta*3.14/180;
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=160&&x<=240)&&(y>=135&&y<=195))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-60.0,-40.0,35.0,55.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=280&&x<=360)&&(y>=135&&y<=195))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0,-10.0,35.0,55.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=40&&x<=120)&&(y>=240&&y<=300))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-90.0,-70.0,0.0,20.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
		//printf("Enter the No. of Circles and Squares in Cylinder and Parallelopiped:");
		//scanf("%d%d",&cyl_n,&par_n);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=160&&x<=240)&&(y>=240&&y<=300))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-60.0,-40.0,0.0,20.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=280&&x<=360)&&(y>=240&&y<=300))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0,-10.0,0.0,20.0,-100.0,100.0);
		glutMouseFunc(0);
		//printf("%d %d\n",x,y);
	}
	else if(button==GLUT_LEFT_BUTTON&&(x>=40&&x<=120)&&(y>=345&&y<=405))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-90.0,-70.0,-35.0,-15.0,-100.0,100.0);
		glutMouseFunc(ccube_mouse);
		glutReshapeFunc(ccube_myReshape);
		glutKeyboardFunc(ccube_keys);
		printf("%d %d\n",x,y);
	}
}
void keyboard(unsigned char c,int x,int y)
{
	if(c=='b')
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(orthoCo[0],orthoCo[1],orthoCo[2],orthoCo[3],orthoCo[4],orthoCo[5]);
		glutMouseFunc(mouse);
		glutReshapeFunc(myReshape);
	}
	else exit(0);
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	     glOrtho(-100.0,20.0,-20.0*(GLfloat)h/(GLfloat)w,100.0*(GLfloat)h/(GLfloat)w,-100.0,100.0);
           else
	    glOrtho(-100.0*(GLfloat)w/(GLfloat)h,20.0*(GLfloat)w/(GLfloat)h,-20.0,100.0,-100.0,100.0);
	    glMatrixMode(GL_MODELVIEW);
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
		glutInitWindowSize(800,600);
		glutCreateWindow("Computer Graphics Project!");
		glutReshapeFunc(myReshape);
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
        glutIdleFunc(idle);
        glutKeyboardFunc(keyboard);
		glEnable(GL_DEPTH_TEST);
		glColor3f(1.0,1.0,1.0);
		//myinit();
		glutMainLoop();
}
