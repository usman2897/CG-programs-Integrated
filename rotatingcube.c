#include<GL/glut.h>
#include<stdio.h>
void polygon(GLfloat a,GLfloat b,GLfloat c,GLfloat d);

GLfloat    cube_vertices[ ]={ -1.0,-1.0,-1.0,
         			   1.0,-1.0,-1.0,
                        1.0, 1.0,-1.0,
            - 1.0, 1.0,-1.0,
    	            - 1.0,-1.0, 1.0,
               1.0,-1.0, 1.0,
               1.0, 1.0, 1.0,
              -1.0, 1.0, 1.0 };

GLfloat    cube_normals[ ]={ -1.0,-1.0,-1.0,
                1.0,-1.0,-1.0,
                1.0, 1.0,-1.0,
               -1.0, 1.0,-1.0,
               -1.0,-1.0, 1.0,
                 1.0,-1.0, 1.0,
                 1.0, 1.0, 1.0,
                -1.0, 1.0, 1.0 };

GLfloat      cube_colors[ ]={   0.0,0.0,0.0,
               1.0,0.0,0.0,
 	   1.0,1.0,0.0,
   0.0,1.0,0.0,
   0.0,0.0,1.0,
   1.0,0.0,1.0,
   1.0,1.0,1.0,
   0.0,1.0,1.0};

GLubyte cube_Indices[]={0,3,2,
1,2,3
,7,6,0
,4,7,3,
1,2,6,5
,4,5,6,
7,0,1,5,4 };
static GLfloat theta[]={0.0,0.0,0.0};
static GLint axis=2;

void cube_mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)axis=0;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) axis=1;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) axis=2;
}
 void cube_spin()
{
	theta[axis]+=0.4;
	if(theta[axis]>360.0)
		theta[axis]-=360.0;
	glutPostRedisplay();
}
void cube_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	     glOrtho(-90.0,-70.0,70.0+0.5*(GLfloat)h/(GLfloat)w,90.0-0.5*(GLfloat)h/(GLfloat)w,-100.0,100.0);
           else
	    glOrtho(-90+0.5*(GLfloat)w/(GLfloat)h,-70.0-0.5*(GLfloat)w/(GLfloat)h,70.0,90.0,-100.0,100.0);
	    glMatrixMode(GL_MODELVIEW);
}
void cube(void)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,cube_vertices);
	glColorPointer(3,GL_FLOAT,0,cube_colors);
	glNormalPointer(GL_FLOAT,0,cube_normals);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glLoadIdentity();
	polygon(-90.0,70.0,90.0,-70.0);
	glPopMatrix();
	glLoadIdentity();
	glPushMatrix();
	glScaled(5.0,5.0,5.0);
	glTranslated(-16.0,16.0,0.0);
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cube_Indices);
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(-92,63);
	Write("Rotating Cube",1);
}
