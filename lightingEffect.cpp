#define GL_SILENCE_DEPRECATION

#include <bits/stdc++.h>
#include <bits/stdc++.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat emerald_ambient[] = {1, 0.0, 0.0}, 
emerald_diffuse[] = {1, 1, 1}, 
emerald_specular[] = {1, 1, 1}, 
emerald_shininess = 100;

// GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0}, 
// green_light[] = {0.0, 1.0, 0.0, 1.0}, 
// white_light[] = {1.0, 1.0, 1.0, 1.0};

GLfloat left_light_position[] = {-1.0, 0.0, 1.0, 0.0}, 
right_light_position[] = {1.0, 0.0, 1.0, 0.0};

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  

GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0}; 

float gg = 0;

double rotate_y = 0; 
double rotate_x = 0;

int mouse_x, mouse_y;
bool RIGHT_BUTTON_DOWN;

void init(void)
{
  glClearColor(0,0,0,0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void processKeys(unsigned char key, int x, int y) {
  glClear(GL_COLOR_BUFFER_BIT);     
  if(key == 'a'){
      gg += 0.01;
  }
  if(key == 's'){
      gg -= 0.01;
  }
  gg = fmin(gg, (float)1.0);
  gg = fmax(gg, (float)0.0);
  glutPostRedisplay();
}

float ver[8][3] = 
{
    {-1.0, -1.0, 1.0},  //a -0 
    {-1.0, 1.0, 1.0},   //b -1
    {1.0, 1.0, 1.0},    //c -2 
    {1.0, -1.0, 1.0},   //d -3
    {-1.0, -1.0, -1.0}, //e -4
    {-1.0, 1.0, -1.0},  //f -5
    {1.0, 1.0, -1.0},   //g -6
    {1.0, -1.0, -1.0},  //h -7
};

GLfloat color[6][3] = 
{
	{0.4, 0.4, 0.4},
	{1.0, 1.0, 1.0},
	{0.7, 0.7, 0.7},
	{0.4, 0.4, 0.4},
    {0.7, 0.7, 0.7},
	{1.0, 1.0, 1.0},
    // {1,0,0},
    // {1,1,0},
    // {1,0,1},
    // {1,0.5,0},
    // {1,0,0.5},
    // {1,1,1},
    
};

void quad(int a,int b,int c,int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);
    glVertex3fv(ver[b]);
    glVertex3fv(ver[c]);
    glVertex3fv(ver[d]);

    glEnd();
}

void colorcube()
{
    quad(0,3,2,1);  //1
	quad(4,5,6,7);  //2
    quad(2,3,7,6);  //3
    quad(0,4,7,3);  //4
	quad(0,1,5,4);  //5
    quad(1,2,6,5);  //6
}

void specialKeys( int key, int x, int y ) 
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

void mouse ( int button, int state, int x , int y )
{
    mouse_x = x;
    mouse_y = y;

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        RIGHT_BUTTON_DOWN = true;
    glutPostRedisplay();
	
}

void motion(int x, int y) {
    if (RIGHT_BUTTON_DOWN) {
        rotate_x += (float)(x - mouse_x) / 4.0; 
        rotate_y += (float)(mouse_y - y) / 4.0;
    }

    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 10 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3, 
               0, 0, 0,
               0, 0, 1
              );

    glRotatef( -rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( -rotate_y, 0.0, 1.0, 0.0 );

    glMaterialfv(GL_FRONT, GL_AMBIENT, emerald_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, emerald_diffuse);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat light_ambient[] = {gg, gg-0.2, gg+0.5, 0.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    colorcube();

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow("Lighting effects");
	init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc( specialKeys );
    glutKeyboardFunc(processKeys);
    glEnable( GL_DEPTH_TEST );
    glutMainLoop();
    return 0;
}