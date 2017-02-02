#include<stdio.h>
#include<GL/glut.h>
#include "ratio.h"
#include "main.h"
#define true 1
#define false 0
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

double lb_xmin=50,lb_ymin=50, lb_xmax=99,lb_ymax=99; // Window boundaries
double lb_xvmin=20,lb_yvmin=20,lb_xvmax=30,lb_yvmax=30; // Viewport boundaries
double lb_x0=0,lb_y0=0,lb_x1=80,lb_y1=120;
GLfloat lb_screen[4]={-60,35,55,-40};
int cliptest(double p, double q, double *t1, double *t2)
{
  double t;
      if(p) t=q/p;  // to check whether p
  if(p < 0.0)    // potentially entry point, update te
  {
	  if( t > *t1) *t1=t;
	  if( t > *t2) return(false); // line portion is outside
  }
  else if(p > 0.0)    //  Potentially leaving point, update tl
  {
	  if( t < *t2) *t2=t;
	  if( t < *t1) return(false); // line portion is outside
  }
  else if(p == 0.0)
	  {
		  if( q < 0.0) return(false); // line parallel to edge but outside
	  }
 return(true);
}
void lb_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(lb_screen[0],lb_screen[3],lb_screen[1],lb_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void LiangBarskyLineClipAndDraw ()
{
	double dx=lb_x1-lb_x0, dy=lb_y1-lb_y0, te=0.0, tl=1.0,vx1,vy1,vx0,vy0;
	if(cliptest(-dx,lb_x0-lb_xmin,&te,&tl))  // inside test wrt left edge
	if(cliptest(dx,lb_xmax-lb_x0,&te,&tl)) // inside test wrt right edge
	if(cliptest(-dy,lb_y0-lb_ymin,&te,&tl)) // inside test wrt bottom edge
	if(cliptest(dy,lb_ymax-lb_y0,&te,&tl)) // inside test wrt top edge
	{
		if( tl < 1.0 )
		{
			lb_x1 = lb_x0 + tl*dx;
			lb_y1 = lb_y0 + tl*dy;
		}
		if( te > 0.0 )
		{  	lb_x0 = lb_x0 + te*dx;
			lb_y0 = lb_y0 + te*dy;
		}

		                // Window to viewport mappings
		double sx=(lb_xvmax-lb_xvmin)/(lb_xmax-lb_xmin); // Scale parameters
		double sy=(lb_yvmax-lb_yvmin)/(lb_ymax-lb_ymin);
		double vx0=lb_xvmin+(lb_x0-lb_xmin)*sx;
		double vy0=lb_yvmin+(lb_y0-lb_ymin)*sy;
		double vx1=lb_xvmin+(lb_x1-lb_xmin)*sx;
		double vy1=lb_yvmin+(lb_y1-lb_ymin)*sy;
			//draw a red colored viewport
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(lb_xvmin,lb_yvmin);
			glVertex2f(lb_xvmax, lb_yvmin);
			glVertex2f(lb_xvmax, lb_yvmax);
			glVertex2f(lb_xvmin, lb_yvmax);
		glEnd();
		glColor3f(0.0,1.0,0.0); // draw blue colored clipped line
		glBegin(GL_LINES);
			glVertex2d (vx0, vy0);
			glVertex2d (vx1, vy1);
		glEnd();
	}
}// end of line clipping
void liangBarsky()
{
	glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
  	  polygon(lb_screen[0],lb_screen[1],lb_screen[2],lb_screen[3]);
	glPopMatrix();
    glColor3f(1.0,0.0,0.0);
	glPushMatrix();
      glLoadIdentity();
      glScaled(0.2,0.2,0.0);
	  glTranslated(-310.0,160.0,0.0);
	  glBegin(GL_LINES);
	    glVertex2d (lb_x0,lb_y0);
	    glVertex2d (lb_x1,lb_y1);
   	  glEnd();

//draw a blue colored window
	  glColor3f(0.0, 0.0, 1.0);
	  glBegin(GL_LINE_LOOP);
  	    glVertex2f(lb_xmin, lb_ymin);
  	    glVertex2f(lb_xmax, lb_ymin);
	    glVertex2f(lb_xmax, lb_ymax);
        glVertex2f(lb_xmin, lb_ymax);
	  glEnd();
	  LiangBarskyLineClipAndDraw();
	glPopMatrix();
	 glColor3f(0.0,0.0,1.0);
	  glRasterPos2f(lb_screen[0]+2,lb_screen[1]-8);
	  Write("LiangBarsky",1);
}
