#include "glut.h"
#include "Sleep.h"
// prototypes
void init(void);
void display(void);
void reshape(int w, int h);
void idle(void);
float yPosition = 0.0;
//declare global variables here

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // single is default
	glutInitWindowSize(500, 500);  // default is 300 x 300
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Second OpenGL Program");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 1;
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color = white
	glColor3f(0.0, 0.0, 0.0);		// drawing color = black
	glLineWidth(2.0f);
	glEnable(GL_DEPTH_TEST);
}


void reshape(int w , int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	// which matrix
	glLoadIdentity();	// initialize the selected matrix
	gluLookAt(
		5.0, 10.0, 20.0,		// x,y,z of eye
		0.0, 0.0, 0.0,		// x,y,z of look at point
		0.0, 1.0, 0.0);		// x,y,z of up vector
		
	glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -100.0, 0.0);
		glVertex3f(0.0,  100.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-100.0, 0.0, 0.0);
		glVertex3f( 100.0, 0.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f( 0.0, 0.0, -100.0);
		glVertex3f( 0.0, 0.0, 100.0);
	glEnd();
	glPushMatrix();
	    glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 0.0);	// unneeded since default position is (0, 0, 0)
		glRotatef(0.0, 1.0, 0.0, 0.0);	// unneeded since default rotation is 0 degrees
		glScalef(1.0, 3.0, 1.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glutSolidCube(0.6);		// size is 0.6
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(2.0, 0.0, -1.0);	// unneeded since default position is (0, 0, 0)
		glRotatef(0.0, 0.0, 0.0, 0.0);	// unneeded since default rotation is 0 degrees
		glScalef(1.0, 1.0, 1.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glutWireSphere(0.9,20,40);		// size is 0.6
	glPopMatrix();
	// add more stuff here to draw other models
	glPushMatrix();
		glTranslatef(0.0, 0.0, -2.0);	// unneeded since default position is (0, 0, 0)
		glRotatef(0.0, 0.0, 0.0, 0.0);	// unneeded since default rotation is 0 degrees
		glScalef(1.0, 3.0, 1.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glutWireCube(0.6);		// size is 0.6
	glPopMatrix();

	glPushMatrix();
			glTranslatef(0.0, yPosition, 0.0f);
	glPushMatrix();
		glTranslatef(0.0, 4.0, 0.0);	// unneeded since default position is (0, 0, 0)
		glRotatef(270.0, 1.0, 0.0, 0.0);	// unneeded since default rotation is 0 degrees
		glScalef(1.0, 3.0, 1.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glutWireCone(1.0,1.5,20,2);		// size is 0.6
	glPopMatrix();

	GLUquadricObj* p_quadric = gluNewQuadric();
	

	glPushMatrix();
		glColor3f(0.5, 0.5, 0.0);
		glRotatef(270, 1, 0, 0);
		gluCylinder(p_quadric, 1.0, 1.0, 4.0, 20, 1); 
		glColor3f(0.5, 0.5, 0.5);
		gluDisk(p_quadric, 0.0, 1.0, 20, 4);
	glPopMatrix();
	glPopMatrix();
	gluDeleteQuadric(p_quadric);

	glFlush();
	glutSwapBuffers();		// display it, double buffering
}

void idle ()
{
	yPosition += 0.1;
		if(yPosition > 10)
			yPosition = 0.0;
		sleep(0.01);
	// tell OpenGL to redisplay as often as possible
	glutPostRedisplay();
}
