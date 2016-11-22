#include<stdio.h>
#include<GL/glut.h>
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

typedef   float  tet_point[3];

tet_point tet_v[]={ {0.0,0.0,1.0},
      {0.0,0.943,-0.33},
      {-0.816,-0.471,-0.33},
      {0.816,-0.471,0.33}};
int tet_n=3;

void  tet_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else

         glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void tet_triangle(tet_point a,tet_point b,tet_point c)
{
	glBegin(GL_POLYGON);
	glNormal3fv(a);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void tet_divide_tri(tet_point a,tet_point b,tet_point c,int m)
{
	tet_point v1,v2,v3;
	int j;
	if (m>0)
	{
		for(j=0;j<3;j++)
			v1[j]=(a[j]+b[j])/2;

		for(j=0;j<3;j++)
			v2[j]=(a[j]+c[j])/2;

		for(j=0;j<3;j++)
			v3[j]=(b[j]+c[j])/2;

		tet_divide_tri(a,v1,v2,m-1);

		tet_divide_tri(c,v2,v3,m-1);

		tet_divide_tri(b,v3,v1,m-1);
	}
else
         	tet_triangle(a,b,c);
}
void tetrahedron(int m)
{
	glPushMatrix();
	glColor3f(0.2,0.2,0.2);
	glLoadIdentity();
	polygon(-30.0,70.0,90.0,-10.0);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glScaled(8.0,8.0,8.0);
	glTranslated(-2.5,9.8,0.0);
	glColor3f(1.0,0.0,0.0);
	tet_divide_tri(tet_v[0],tet_v[1],tet_v[2],m);
	glColor3f(0.0,1.0,0.0);
	tet_divide_tri(tet_v[3],tet_v[2],tet_v[1],m);
	glColor3f(0.0,0.0,1.0);
	tet_divide_tri(tet_v[0],tet_v[3],tet_v[1],m);
	glColor3f(1.0,1.0,0.0);
	tet_divide_tri(tet_v[0],tet_v[2],tet_v[3],m);
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(-31,63);
	Write("Tetrahedron",1);
}
