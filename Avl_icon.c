#include<GL/glut.h>
#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ratio.h"
#include "main.h"

//declarations
void polygon(GLfloat a,GLfloat b,GLfloat c,GLfloat d);
extern int count;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };        /*Variables used for lighting and shading effects*/
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

GLfloat avl_color[2][3]={{1.0,0.0,0.0},{0.0,0.0,1.0}};
float left_angle = -150;
float right_angle = 150;

struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};
void drawNode(struct node* t_root,float x1,float y1,int level);

struct node *icon,*current=NULL;
struct node* newNode(int key)
{
    struct node* node = (struct node *)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  /* New node is initially added at leaf*/
    current=node;
    return(node);
}
void createIcon()
{
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    left_angle = -150;
	right_angle = 150;
	icon=newNode(2);
	icon->left=(struct node*)newNode(1);
	icon->right=(struct node*)newNode(3);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScaled(3,3,3);
	glTranslated(-1,-30,0);
	drawNode(icon,10,50,0);
	glPopMatrix();
	glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    left_angle=245;
    right_angle=115;
	if(count%10) glColor3fv(avl_color[(count/10)%2]);
	glRasterPos2f(20,5);
	Write("AVL Tree",2);
}

/* Function to draw a line to connect nodes */
void draw_line(float x1,float y1,float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
/* Function to display the text */
void draw_text(char* text,float x, float y)
{
    int i;
    glRasterPos3f(x-0.5,y-0.5,1.5);
    for (i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

/* A recursive function to draw a binary tree */
void drawNode(struct node *t_root,float x1,float y1,int level)
{
    char buff[5];
    if (t_root==NULL)
    	return;
    float radius = 1.5;
    float branch_length = 12 - level*2.5;
    float angle_change = 15;

    /* Draw the current node */
    if(t_root==current)
        glColor3f(0.0,1.0,0.0);           /* If the node to be drawn is the currently inputted node
                                Set color of node to green until its placed in its position */
    else
        glColor3f(1.0,0.0,0.0);     /* else set color of node to red */

    glPushMatrix();
        glTranslated(x1,y1,0);              /* Draw the node*/
        glutSolidSphere(radius,50,50);
    glPopMatrix();

    sprintf(buff,"%d",t_root->key); //atoi
    glColor3f(1.0,1.0,1.0);
    draw_text(buff,x1,y1);
            /* Display value of the node*/

    if(t_root->left)    /*Checks if parent has a left child node to be drawn*/
    {
        /* Draw the left child node */
        float angle = left_angle - level*angle_change;
        double radian = angle*3.14/180;
        //float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->left,x2,y2,level+1);
        glColor3f(0.0,0.0,0.0);
        draw_line(x1,y1,x2,y2);
    }
    if(t_root->right) /*Checks if parent has a Right child node to be drawn*/
    {
        /* Draw the Right child node */
        float angle = right_angle + level*angle_change;
        float radian = angle*3.14/180;
        //float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->right,x2,y2,level+1);

        glColor3f(0.0,0.0,0.0);
        draw_line(x1,y1,x2,y2);
    }
}
