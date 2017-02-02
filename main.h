#define true 1
#define false 0
#define outcode int

void myReshape(int,int);
outcode ComputeOutCode (double x, double y);
void keyboard(unsigned char c,int x,int y);
void mouse(int button,int status,int x,int y);
void Write(char *string,int size);

//tetrahedron
void tetrahedron(int );
void  tet_myReshape(int w,int h);

//cube_data
void cube_mouse(int btn,int state,int x,int y);
void cube_spin();
void cube_myReshape(int w,int h);
void cube(void);
extern GLfloat cube_screen[];

//teapot
void tp_myReshape(int w,int h);
extern GLfloat tp_screen[];

//tetrahedron
extern int tet_n;
void  tet_myReshape(int w,int h);
extern GLfloat tet_screen[];

//house
extern GLfloat house_theta;
extern GLfloat house_screen[];
void house_myReshape(int w,int h);

//liangBarsky
extern GLfloat lb_screen[];
void lb_myReshape(int w,int h);
//CohenSutherland
extern GLfloat cohen_screen[];
void cohen_myReshape(int w,int h);
//Cylinder_Parallelopiped
extern GLfloat parcyl_screen[];
void parcyl_myReshape(int w,int h);
//mesh_data
extern GLfloat mesh_screen[];
void mesh_myReshape(int w,int h);
//scanfill
extern GLfloat sf_screen[];
void sf_myReshape(int w,int h);
//Viewing a cube
void ccube_mouse(int btn, int state, int x, int y);
void ccube_keys(unsigned char key, int x, int y);
void cbv_myReshape(int w, int h);
void ccube();
extern GLfloat cbv_screen[];

//avl
void avl_display();
void avl_myReshape (int , int);
void avl_keyboard(unsigned char,int,int);

//icons
void cube();
void teapot();
void tetrahedron(int tet_n);
void home();
void liangBarsky();
void cohenSutherland();
void cylPara();
void mesh();
void polyfill();
void ccube();
void createIcon();