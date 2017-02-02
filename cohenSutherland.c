#include<stdio.h>
#include<GL/glut.h>
#include "ratio.h"
#define true 1
#define false 0
#define outcode int
void polygon(GLfloat,GLfloat,GLfloat,GLfloat);

double cohen_xmin=50,cohen_ymin=50, cohen_xmax=100,cohen_ymax=100; // Window boundaries
double cohen_xvmin=200,cohen_yvmin=200,cohen_xvmax=300,cohen_yvmax=300; // Viewport boundaries
double cohen_x0=120,cohen_y0=10,cohen_x1=40,cohen_y1=130;
//int x1, x2, y1, y2;
//bit codes for the right, left, top, & bottom
const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;
GLfloat cohen_screen[4]={-30,35,55,-10};

void CohenSutherlandLineClipAndDraw (double cohen_x0,double cohen_y0,double cohen_x1,double cohen_y1)
{
	//Outcodes for P0, P1, and whatever point lies outside the clip rectangle
	outcode outcode0, outcode1, outcodeOut;
	int accept = false, done = false;

	//compute outcodes
	outcode0 = ComputeOutCode (cohen_x0, cohen_y0);
	outcode1 = ComputeOutCode (cohen_x1, cohen_y1);

	do{
		if (!(outcode0 | outcode1))      //logical or is 0 Trivially accept & exit
		{
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1)   //logical and is not 0. Trivially reject and exit
			done = true;
		else
		{
			//failed both tests, so calculate the line segment to clip
			//from an outside point to an intersection with clip edge
			double x, y;

			//At least one endpoint is outside the clip rectangle; pick it.
			outcodeOut = outcode0? outcode0: outcode1;

			//Now find the intersection point;
			//use formulas y = y0 + slope * (x - x0), x = x0 + (1/slope)* (y - y0)
			if (outcodeOut & TOP)          //point is above the clip rectangle
			{
				x = cohen_x0 + (cohen_x1 - cohen_x0) * (cohen_ymax - cohen_y0)/(cohen_y1 - cohen_y0);
				y = cohen_ymax;
			}
			else if (outcodeOut & BOTTOM)  //point is below the clip rectangle
			{
				x = cohen_x0 + (cohen_x1 - cohen_x0) * (cohen_ymin - cohen_y0)/(cohen_y1 - cohen_y0);
				y = cohen_ymin;
			}
			else if (outcodeOut & RIGHT)   //point is to the right of clip rectangle
			{
				y = cohen_y0 + (cohen_y1 - cohen_y0) * (cohen_xmax - cohen_x0)/(cohen_x1 - cohen_x0);
				x = cohen_xmax;
			}
			else                           //point is to the left of clip rectangle
			{
				y = cohen_y0 + (cohen_y1 - cohen_y0) * (cohen_xmin - cohen_x0)/(cohen_x1 - cohen_x0);
				x = cohen_xmin;
			}

			//Now we move outside point to intersection point to clip
			//and get ready for next pass.
			if (outcodeOut == outcode0)
			{
				cohen_x0 = x;
				cohen_y0 = y;
				outcode0 = ComputeOutCode (cohen_x0, cohen_y0);
			}
			else
			{
				cohen_x1 = x;
				cohen_y1 = y;
				outcode1 = ComputeOutCode (cohen_x1, cohen_y1);
			}
		}
	}while (!done);

	if (accept)
	{                // Window to viewport mappings
		double sx=(cohen_xvmax-cohen_xvmin)/(cohen_xmax-cohen_xmin); // Scale parameters
		double sy=(cohen_yvmax-cohen_yvmin)/(cohen_ymax-cohen_ymin);
		double vx0=cohen_xvmin+(cohen_x0-cohen_xmin)*sx;
		double vy0=cohen_yvmin+(cohen_y0-cohen_ymin)*sy;
		double vx1=cohen_xvmin+(cohen_x1-cohen_xmin)*sx;
		double vy1=cohen_yvmin+(cohen_y1-cohen_ymin)*sy;
			//draw a red colored viewport
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(cohen_xvmin, cohen_yvmin);
			glVertex2f(cohen_xvmax, cohen_yvmin);
			glVertex2f(cohen_xvmax, cohen_yvmax);
			glVertex2f(cohen_xvmin, cohen_yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0); // draw blue colored clipped line
		glBegin(GL_LINES);
			glVertex2d (vx0, vy0);
			glVertex2d (vx1, vy1);
		glEnd();
	}
}
outcode ComputeOutCode (double x, double y)
{
	outcode code = 0;
	if (y > cohen_ymax)              //above the clip window
		code |= TOP;
	else if (y < cohen_ymin)         //below the clip window
		code |= BOTTOM;
	if (x > cohen_xmax)              //to the right of clip window
		code |= RIGHT;
	else if (x < cohen_xmin)         //to the left of clip window
		code |= LEFT;
	return code;
}
void cohen_myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(cohen_screen[0],cohen_screen[3],cohen_screen[1],cohen_screen[2],-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    width=w;height=h;cal_ratio(orthoCo);
}
void cohenSutherland()
{
	glColor3f(0.2,0.2,0.2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glLoadIdentity();
  	  polygon(cohen_screen[0],cohen_screen[1],cohen_screen[2],cohen_screen[3]);
	glPopMatrix();
	glPushMatrix();
	  glLoadIdentity();
	  glScaled(0.05,0.05,0.0);
	  glTranslated(-550.0,750.0,0.0);
	  glColor3f(1.0,0.0,0.0);
	  glBegin(GL_LINES);
  	    glVertex2f (cohen_x0, cohen_y0);
	    glVertex2f (cohen_x1, cohen_y1);
	    glVertex2f (60,20);
	    glVertex2f (80,120);
	  glEnd();

//draw a blue colored window
	  glColor3f(0.0, 0.0, 1.0);
	  glBegin(GL_LINE_LOOP);
  	    glVertex2f(cohen_xmin, cohen_ymin);
        glVertex2f(cohen_xmax, cohen_ymin);
        glVertex2f(cohen_xmax, cohen_ymax);
  	    glVertex2f(cohen_xmin, cohen_ymax);
	  glEnd();
	  CohenSutherlandLineClipAndDraw(cohen_x0,cohen_y0,cohen_x1,cohen_y1);
	  CohenSutherlandLineClipAndDraw(60,20,80,120);
	  glPopMatrix();
	  glLoadIdentity();
	  glColor3f(0.0,0.0,1.0);
	  glRasterPos2f(cohen_screen[0]+2,cohen_screen[1]-8);
	  Write("CohenSutherLand",1);
}
