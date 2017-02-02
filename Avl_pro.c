#include<GL/glut.h>
#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ratio.h"
#define max(x, y) (((x) > (y)) ? (x) : (y))

//external variables;
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};
extern struct node *current;
extern const GLfloat light_ambient[];  
extern const GLfloat light_diffuse[];          /*Variables used for lighting and shading effects*/
extern const GLfloat light_specular[]; 
extern const GLfloat light_position[]; 

extern const GLfloat mat_ambient[];
extern const GLfloat mat_diffuse[];   
extern const GLfloat mat_specular[];  
extern const GLfloat high_shininess[];
int c=0;
int result=0,page=0;
struct node* root = NULL;
extern GLfloat orthoCo[];
extern int l;
extern int width;
extern int height;
//main
void display();
void mouse(int button,int status,int x,int y);
void keyboard(unsigned char c,int x,int y);
void myReshape(int w,int h);
void idle();
//Previous Declaration
void draw_line(float x1,float y1,float x2, float y2);
void draw_line(float x1,float y1,float x2, float y2);
extern struct node* newNode(int);
void draw_text(char* text,float x, float y);
void drawNode(struct node *t_root,float x1,float y1,int level);
void Write(char *string,int size);
struct node* delete(struct node* r);
void enablelight();
void disablelight();

//function Prototye
void avl_help();
void printAbout();
void drawFirstPage();
void avl_display();

void init()
{
	enablelight();
	glClearColor(0.5,0.5,0.1,1.0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
/* A utility function to get height of the tree*/
int high(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
/* A utility function to right rotate subtree rooted with y*/
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(high(y->left), high(y->right))+1;
    x->height = max(high(x->left), high(x->right))+1;

    // Return new root
    return x;
}

/* A utility function to left rotate subtree rooted with x */
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(high(x->left), high(x->right))+1;
    y->height = max(high(y->left), high(y->right))+1;

    // Return new root
    return y;
}

/* Function to Get Balance factor of node N */
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return high(N->left) - high(N->right);
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}
/* Function to Insert a node into the tree and perform balancing*/
struct node* insert(struct node* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));

	    usleep(10);

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    avl_display();      /* Display Tree after normal BST Insertion */

    usleep(500000);

    /* 2. Update height of this ancestor node */
    node->height = max(high(node->left), high(node->right)) + 1;


    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int bal = getBalance(node);

    /* Left Left Rotation case */
    if (bal > 1 && key <= node->left->key)
        return rightRotate(node);

    /* Right Right Rotation case */
    if (bal < -1 && key >= node->right->key)
        return leftRotate(node);

    /* Left Right Rotation case */
    if (bal > 1 && key >= node->left->key)
    {
        node->left =  leftRotate(node->left);
        avl_display();
        usleep(500000);
        return rightRotate(node);
    }

   /* Right Left Rotation case */
    if (bal < -1 && key <= node->right->key)
    {
        node->right = rightRotate(node->right);

        avl_display();
        usleep(500000);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct node* deleteNode(struct node* root1, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root1 == NULL)
        return root1;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( key < root1->key )
        root1->left = deleteNode(root1->left, key);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( key > root1->key )
        root1->right = deleteNode(root1->right, key);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root1->left == NULL) || (root1->right == NULL) )
        {
            struct node *temp = root1->left ? root1->left :
                                             root1->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root1;
                root1 = NULL;
            }
            else // One child case
             *root1 = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct node* temp = minValueNode(root1->right);
 
            // Copy the inorder successor's data to this node
            root1->key = temp->key;
 
            // Delete the inorder successor
            root1->right = deleteNode(root1->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root1 == NULL)
      return root1;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root1->height = 1 + max(high(root1->left),
                           high(root1->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root1);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root1->left) >= 0)
        return rightRotate(root1);
 
    // Left Right Case
    if (balance > 1 && getBalance(root1->left) < 0)
    {
        root1->left =  leftRotate(root1->left);
        return rightRotate(root1);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root1->right) <= 0)
        return leftRotate(root1);
 
    // Right Left Case
    if (balance < -1 && getBalance(root1->right) > 0)
    {
        root1->right = rightRotate(root1->right);
        return leftRotate(root1);
    }
 
    return root1;
}


void avl_display()
{
	if(!c){
		init();c++;
	}
	if(page==0)
    {
		glClearColor (0.9,0.8,0.3,1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0,10,-30);
        glColor3f(0.0,0.0,0.0);

        drawFirstPage();
        glutSwapBuffers();
    }
    if(page==1)
    {
        glClearColor (0.8,0.9,0.3,1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0,8,-30);
        glColor3f(0,0,0);
        glPushMatrix();
        disablelight();
        glRasterPos2f(0,6);
        Write("AVL Tree",2);
        glColor3f(1.0,0.0,0.0);
        glRasterPos2f(-20,4);
        Write("Enter the Number,Then press 'z' to insert or 'd' to delete.",1);
        glRasterPos2f(-20,3);
        Write("Press 'x' to return to AVL Tree or Press 'b' to return to Main Menu",1);
		enablelight();
		glPopMatrix();
        drawNode(root,0,0,0);
        glutSwapBuffers();
    }
    if(page==2)
    {
        glClearColor (0.3,0.8,0.9,1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0,10,-30);
        glColor3f(1,1,1);
        printAbout();
        glutSwapBuffers();
    }

    if(page==3)
    {
        glClearColor (0.8,0.3,0.9,1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0,10,-30);
        glColor3f(1,1,1);
        avl_help();
        glutSwapBuffers();
    }

}

void avl_help()
{
	int i;
    char buffer[100]="HELP";
    glColor3f(0.0,0.0,0.0);
    glRasterPos3f(-10,-0.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

     strcpy(buffer,"1.Press 1 to Start,then Enter any number and press z to display.");
    glRasterPos3f(-20,-5.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);


    strcpy(buffer,"2. Press 2 to Know about AVL tree. ");
    glRasterPos3f(-20,-9,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer,"3. Negative numbers and Deletion of node is not supported.");
    glRasterPos3f(-20,-11,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer,"4. Press b to return to MainMenu.");
    glRasterPos3f(-20,-15,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer,"5. Press 4 to exit");
    glRasterPos3f(-20,-17,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

}
void printAbout()
{
    int i;
    char buffer[50]="What is an AVL tree?. ";
    glColor3f(0.0,0.0,0.0);
    glRasterPos3f(-11,-0.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

     strcpy(buffer,"1.AVL tree is a self-balancing binary search tree");
    glRasterPos3f(-11,-5.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);


    strcpy(buffer,"2. The heights of the two child subtrees of ");
    glRasterPos3f(-11,-9,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer," any node differ by at most one ");
    glRasterPos3f(-11,-11,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer,"3. If at any time they differ by more than one,");
    glRasterPos3f(-11,-15,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);

    strcpy(buffer,"     rebalancing is done to the tree ");
    glRasterPos3f(-11,-17,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);


}
void drawFirstPage()
{
    int i;
    char buffer[50]="AVL TREE CONSTRUCTION ";
    glColor3f(0.0,0.0,0.0);

    glRasterPos3f(-9,1,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

    strcpy(buffer,"1. START");
    glRasterPos3f(-5,-5.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

    strcpy(buffer,"2. ABOUT");
    glRasterPos3f(-5,-11,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

    strcpy(buffer,"3. HELP");
    glRasterPos3f(-5,-16.5,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

    strcpy(buffer,"4. EXIT");
    glRasterPos3f(-5,-22,1.5);
    for (i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
}

void avl_myReshape (int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
    width=w;height=h;
}

struct node* delete(struct node* r)
{
	if(r==NULL)return NULL;
	r->left=delete(r->left);
	r->right=delete(r->right);
	free(r);
	r=NULL;
	return NULL;
}
void avl_back()
{
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(orthoCo[0],orthoCo[3],orthoCo[1],orthoCo[2],-100.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,0.7,0.5,1.0);
	disablelight();
	glutPostRedisplay();
	page=0;c=0;
	root=delete(root);
}
void avl_keyboard(unsigned char key,int x,int y)
{
    if(page==0)
    {
        switch(key)
        {
            case '1':
                page=1;
                avl_display();
                break;

            case '2':
                page=2;
                avl_display();
                break;

            case '3':
                page=3;
                avl_display();
                break;

            case '4':
                exit(0);
        }
    }
    else if(page==1)
    {
        switch(key)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                result=result*10+(key-'0');
                break;
            case 'z':
                root=insert(root,result);
               usleep(5);
                avl_display();
                result=0;
                break;
            case 'd': root=deleteNode(root,result);
            	usleep(5);
            	avl_display();
            	result=0;break;
            case 'x':
               page=0;
               root=delete(root);
               avl_display();
            }
    }
    else if(page==2)
    {
            page=0;
            avl_display();
    }
    else if(page==3)
    {
            page=0;
            avl_display();
    }
    if(key=='b')
    {
    	avl_back();
    }
}
