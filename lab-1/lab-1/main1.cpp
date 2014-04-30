#include "glut.h"
#include "Sleep.h"
// prototypes
void display(void);
void idle(void);
void keyboard(unsigned char key, int x, int y);
void special(int special_key, int x, int y);
float theta=0.0;
float xPosition = 0.0;
float yPosition = 0.75;
       float xIncrement = 0.01;
	   
//declare global variables here

int main(int argc, char** argv)
{
	// initialize OpenGL; pass it the command line arguments
	glutInit(&argc, argv);	
	
	glutCreateWindow("First OpenGL Program");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	glutMainLoop();
	
	return 1;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
       glPushMatrix();
	   glTranslatef(xPosition, yPosition, 0.0f);
		    
       glScalef(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	    glColor3f(0.3, 0.2, 0.1);
		glVertex2f(-0.5,0.25);
		glVertex2f(-0.25, 0.5);
		glVertex2f(0.25,0.5);
		//glColor3f(0.6, 0.6, 0.3);
		glVertex2f(0.5,0.25);
		glVertex2f(0.5,-0.25);
		glVertex2f(0.25,-0.5);
		glVertex2f(-0.25,-0.5);
		glVertex2f(-0.5,-0.25);
	
	glEnd();
	 glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
       glPushMatrix();    // copies existing top matrix
            glRotatef(theta, 0.0f, 0.5f, 1.0f);
	       
	        glBegin(GL_POLYGON);
	    glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.25, 0.5);
		glVertex2f(0.25, 0.5);
		glColor3f(1.0, 0.45, 0.7);
		glVertex2f(0.5, 0);
		glVertex2f(0.25, -0.5);
		glVertex2f(-0.25,-0.5);
	glEnd();
	glPopMatrix();
	
	// ensure that all buffered OpenGL commands get done
	glFlush();	
}



void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case 'a':
	       xPosition -= xIncrement;
           break;
  case 'd':
          xPosition += xIncrement;
       break;

  case 'w' : 
	  yPosition += xIncrement;
	   break;
  case 's':
	  yPosition -= xIncrement;
	   break;
  case 27: // on [ESC]
       exit(0); // normal exit
       break;
  }
}


void special(int special_key, int x, int y)
{
  switch(special_key)
  {
  case GLUT_KEY_LEFT:
       theta += 2.0;
       if(theta >= 360.0)
            theta -= 360.0;
       break;
  case GLUT_KEY_RIGHT:
       theta -= 2.0;
       if(theta >= 360.0)
            theta -= 360.0;
       break;
  }
}
void idle(void)
{
	//xPosition += xIncrement;
      // if(xPosition > 1 || xPosition < -1)
        //    xIncrement = -xIncrement;
	
	//sleep(0.01);
	glutPostRedisplay();
}