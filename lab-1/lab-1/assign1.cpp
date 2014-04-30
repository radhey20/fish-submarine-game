// Name Radhey Shah, Id:200333585, 
//Assignment-1, CS-409

//length of sea goes from 0 to 1000, width 0 to 10000 and depth 0 to -1000;
#include "Sleep.h"
#include <math.h>
#include <stdio.h>
#include <string>
//#include "GetGlut.h"
#include "fish.h"
#include "submarine1.h"
//#include "ObjLibrary/SpriteFont.h"
#include <iostream>
#include <sstream>
#include <time.h> 
#include "alut.h"
#include"LinkedList.h"
#define FILENAME "FreedomDance.wav"


const float SHARK_MASS = 10.0;

const float SHARK_MAX_SPEED = 50.0;

const float SHARK_ACCELERATION = 25.0;

const float SHARK_RADIUS = 5.0;

const float SHARK_ESCORT_DISTANCE = 25.0;

const float SHARK_ARRIVAL_SLOW_DISTANCE = 50.0;

const float SHARK_DETECT_FISH_RADIUS = 200.0;

const float SHARK_EXPLORE_CLOSE_ENOUGH = 50.0;

const float SHARK_PURSUIT_LOOK_AHEAD_FACTOR = 0.025;





using namespace std;

 void playSound();
  void loadSound();
  void cleanUpSound();
/*Luint source[5];
ALenum     format;
ALsizei    size;
ALsizei    freq;
ALboolean  loop;
ALvoid*    data;
ALuint buffers[5];*/
// prototypes
void init(void);
void display(void);
void reshape(int w, int h);
void idle(void);
   //submarine is at depth 500
float depth_color;
float physics_lag=0;
float physics_delta_time;
float AI_lag=0;
float AI_delta_time;
float ai_slow_value;
float delta_time;
int frame;
bool shark_target_fish;
//float vxs;
//float vys;
//float vzs;
//float buoyancy=0.8;
//float horizontal_angle;
//bool update;
//float angle_sub;
bool fog_status;
bool sphere;
void keyboard(unsigned char key, int x, int y);
void special(int special_key, int x, int y);
//void submarine();           //shape and Position of submarine
//void depth_background();    //decide the background color according to the depth
 fish fis;                   //object of class fish
 submarine1 sub;
//void submarine_update();
//void submarine_physics_update();
//void submarine_turn_rate();
//void submarine_turn_clockwise();
//void submarine_horizontal_velocity();
 void physics_update_whale();
 void fast_AI_Whale();
 void whale_model();
 void fog_enable(); 
 void fog_disable();
  void submarine_shark_collision();
SpriteFont font;
ObjModel spiky_obj;
ObjModel submarine_obj;
ObjModel submarine_body;
ObjModel whale_body;
float p_whale_x;
float p_whale_y;
float p_whale_z;
float v_whale_x;
float v_whale_y;
float v_whale_z;
float dv_whale_x;
float dv_whale_y;
float dv_whale_z;
int target_fish_no;
void fast_AI_whale3();
void slow_AI_whale1();
bool fast_AI_ESCORT;
float pwx;
float pwy;
float pwz;
bool key_pressed[256];
void background_sound ();
Vector3 c(sub.xPosition,sub.yPosition,sub.zPosition+40);
Vector3 q(sub.xPosition,sub.yPosition,sub.zPosition-40);
//Vector3 vect;
//declare global variables here


int main(int argc, char** argv)
{   
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);  // single is default
	glutInitWindowSize(500, 500);  // default is 300 x 300
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Second OpenGL Program");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	font.load("Font.bmp");
	
	init();
	glutMainLoop();
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void init(void)
{
	
	glClearColor(0.0, 0.0, 1.0, 1.0);	// background color = white
	glColor3f(0.0, 0.0, 0.0);		// drawing color = black
	glLineWidth(2.0f);
	glEnable(GL_DEPTH_TEST);
	fog_status=true;
	//fog_enable();
	physics_delta_time=(1/PHYSICS_UPDATE_RATE);
	AI_delta_time=(1/_FAST_AI_UPDATE_RATE);
	ai_slow_value=SLOW_AI_UPDATE_FRACTION;
	delta_time=0;
	frame=0;
	spiky_obj.load("fish.obj");
	submarine_obj.load("submarine_body.obj");
	whale_body.load("whale4s.obj");
	p_whale_x=525;
    p_whale_y=500;
    p_whale_z=-500;
	pwx=525;
    pwy=500;
    pwz=-500;
    v_whale_x=8;
    v_whale_y=8;
    v_whale_z=-12; 
	dv_whale_x=0;
    dv_whale_y=0;
    dv_whale_z=0;
	fast_AI_ESCORT=true;
	target_fish_no=-99;
	sphere=false;
	shark_target_fish=false;
	for(int i=0;i<256;i++)
	{
		key_pressed[i]=false;
	}
	alutInit(0, NULL);
//	alutLoadWAVFile("FreedomDance.wav", &format, &data, &size, &freq, &loop);

// Generate the sources


}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void reshape(int w , int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (double)w / (double)h, 0.2, 1500);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void display(void)
{  
	 
	
 // glFlush ();
	stringstream ss,sr,st,sd,phy,AI,slow,frame1;        //for three different font on the screen.
	string radh;
	/*if(fog_status==true)
	{
	fog_enable();
	}
	else
	{
		fog_disable();
	}
	*/

	float depth=0.9;                
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	// which matrix
	glLoadIdentity();	// initialize the selected matrix
	
	Vector3 subvelo(sub.vxs,0,sub.vzs);
	Vector3 unit_vect;
	
	Vector3 look(sub.xPosition,sub.yPosition,(sub.zPosition));
	Vector3 c(sub.xPosition,sub.yPosition,sub.zPosition+40);
	
	float speed= subvelo.getNorm();

	if(speed!=0)
	{
	unit_vect=subvelo.getNormalized();
	unit_vect=unit_vect*40;
	c= look - unit_vect;
	q= look + unit_vect;
	}

	float deltaX=  40*sin((sub.angle_sub)*0.0174532925);
	float deltaZ=  40*cos((sub.angle_sub)*0.0174532925);
	Vector3 des(deltaX,0,deltaZ);
	c=look-des;
	q=c+des;
	//cout<<c.x<<"  "<<c.y<<"  "<<c.z<<endl;
	gluLookAt(                     //camera will move if submarine moves, z position of eye will remain fixed so that submarine remain constant
		c.x, c.y, c.z,		       // x,y,z of eye
		q.x, q.y, q.z,		  // x,y,z of look at point
		0.0, 1.0, 0.0 );		  // x,y,z of up vector
	
		//cout<<"asaf"<<q.x<<"  "<<q.y<<"  "<<q.z<<endl;
	fis.floor_surface();
	ss << "X: " <<sub.xPosition<<" Y:  "<<sub.yPosition<<" z:  "<<sub.zPosition;
	radh=ss.str();
	if(sub.yPosition>1000)
	{
	sub.skybox(sub);
	}
	

	sub.depth_background();             //background color according to depth
	                    //position and shape of submarine
	// add more stuff here to draw other models
	
	fis.fish_position_color(spiky_obj);      //this will position and color the fish
	if(fis.is_diamond()==1)
	{
	whale_model();
	}
	sub.submarine(submarine_obj);
    

	// detect submarine is close enough to fish or not

	

	if(fis.is_finish())      //whether 10 fish is catched or no
	{                        //If catched then game over
	char store;
	
	

	
	
	SpriteFont::setUp2DView(640, 480);
	font.draw("Game Over, You Win", 150,150,SpriteFont::BOLD); //game over 
	SpriteFont::unsetUp2DView();
	int total=fis.no_fish();
	int score=fis.my_score();
	string sco;
	st<<"Score: "<<score;
	sco=st.str();
	sr << "Total_fish: " <<total;
	string rad=sr.str();
	SpriteFont::setUp2DView(640, 480);
	font.draw(radh, 350,30,SpriteFont::BOLD);
	font.draw(rad,30,30,SpriteFont::BOLD);
	font.draw(sco,30,450);
	SpriteFont::unsetUp2DView();
	glFlush();
	glutSwapBuffers();	
	
	sleep(5);        //wait for 5 seconds and then exit
	exit(1);
	
	}




	if(fis.is_diamond()==1)
	{
		
		
	SpriteFont::setUp2DView(640, 480);
	//font.draw("Bonus!!! Dont worry about the depth", 20,50,SpriteFont::BOLD);
	
	SpriteFont::unsetUp2DView();
		
	}
	int total=fis.no_fish();
	int score=fis.my_score();
	string sco;
	string physics;
	string AI_delta;
	string slow_AI;
	string frame_rate;
	AI<<"AI_delta_time: "<<AI_delta_time<<" sec";
	phy<<"Physics_delta_time: "<<physics_delta_time<<" sec";
	slow<<"Slow_AI_update: "<<ai_slow_value<<" sec";
	frame1<<"frame_rate: "<<frame<<" fps";
	physics=phy.str();
	AI_delta=AI.str();
	slow_AI=slow.str();
	frame_rate=frame1.str();
	st<<"Score: "<<score;
	sco=st.str();
	sr << "Total_fish: " <<total;
	string rad=sr.str();
	SpriteFont::setUp2DView(640, 480);
	font.draw(radh, 300,20,SpriteFont::BOLD);
	font.draw(rad,30,20,SpriteFont::BOLD);
	font.draw(sco,30,450);
	//font.draw(physics,30,410);
	//font.draw(AI_delta,350,410);
	//font.draw(slow_AI,200,380);
	//font.draw(frame_rate,200,50);
	SpriteFont::unsetUp2DView();
	 static int shouldPlaySound = 1;
	 //glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
 // glClearColor(0,0,0,1);
 
	
 

	 
	 fis.background_sound();

	glFlush();
	glutSwapBuffers();		// display it, double buffering
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////





// 
void keyboard(unsigned char key, int x, int y)
{

  key_pressed[key] = true;
  switch(key)
  {

  case 'p':

	  sub.sphe=true;
	  fis.sphere=true;
	  break;

  case ';':
	  sub.sphe=false;
	  fis.sphere=false;
	  break;

  case 'D':
	      

	  
	  
      // sub.submarine_turn_clockwise();
	 
	  
	       

           break;


  case 'A':
	 
	    
		break;

  case 'S' : 
	 
		  sub.submarine_decreasing_velocity();
	  
	  
	  
	   break;


  case 'W':
	  

	  

	  
	  
        //sub.submarine_horizontal_velocity();
	  
	  
	  
	   break;
	  
	  
	   



	   case 'd':
	      

		      sub.submarine_turn_clockwise();
	  
		   /*sub.psx=sub.xPosition;
		  sub.xPosition=sub.xPosition+1;
	 */
	  
	       

        break;


  case 'a':


	        sub.submarine_turn_rate();
	  
	  
          
       break;
	     
	     /* sub.psx=sub.xPosition;
		  sub.xPosition=sub.xPosition-1;
	 */
	  
          
         

  case 's' : 
	      
	       sub.submarine_decreasing_velocity();
	  
	  
	  
	   
	     /* sub.psy=sub.yPosition;
		  sub.yPosition=sub.yPosition-1*/;
	  
	  
	  
	   break;


  case 'w':
	 
	      sub.submarine_horizontal_velocity();
	   /* sub.psy=sub.yPosition;
        sub.yPosition=sub.yPosition+1;
	  */
	  
	  
	   break;


	   case 'Y':
	 
	  
        sub.submarine_horizontal_velocity();
	  
	  
	  
	   break;





	   case 'y':
		   if(physics_delta_time<=2.0)
		   {
		   physics_delta_time+=0.002;
		   }
	     
	  break;


	  case 'h':
		   if(physics_delta_time>=0.002)
		   {
		   physics_delta_time-=0.002;
		   }
	     
	 break;


	 case 'u':
		   if(AI_delta_time<=2.0)
		   {
			   AI_delta_time+=0.002;
		   }
     break;


		   case 'j':
		   if(AI_delta_time>=0.002)
		   {
			   AI_delta_time-=0.002;
		   }
		   break;


		   case 'i':
			   ai_slow_value= fis.ai_increment();
		   break;


		   case 'k':
		
		   
			   ai_slow_value=fis.ai_decrement();
		   
		   break;

		    case 't':
				fis.fish_increment();
		   break;


		    case 'g':
				fis.fish_decrement();
		   break;


		   case 'o':
			   fog_enable();
			   fis.is_culling=true;
			       // fog_status=true;
			break;


		   case 'l':
			       //fog_status=false;
			   fis.is_culling=false;
			   fog_disable();
			break;

		   case' ':
			   if(fast_AI_ESCORT==true)
			   {
				   fast_AI_ESCORT=false;
			   }
			   else
			   {
				   fast_AI_ESCORT=true;
			   }
			   shark_target_fish=false;
			   break;

          case 27: // on [ESC]
               exit(0); // normal exit
           break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////


void special(int special_key, int x, int y)
{
  switch(special_key)
  {
  case GLUT_KEY_DOWN:
	 

	 sub.psy=sub.yPosition;
	 sub.yPosition=sub.yPosition-2;
	 //sub.buoyancy_decrease();
	 
       break;
  case GLUT_KEY_UP:

	 // sub.buoyancy_increase();
	 


     sub.psy=sub.yPosition;
     sub.yPosition=sub.yPosition+2;
	  break;
	   
  }
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////
void idle ()
{
	/*sub.yPosition += 0.1;
		if(sub.yPosition > 10)
			sub.yPosition = 0.0;
		sleep(0.01);*/
	// tell OpenGL to redisplay as often as possible
	 
	float current_time = glutGet(GLUT_ELAPSED_TIME)/1000.0f; 
    static float previous_time;
	static float mytime;
	static bool rad=false;
	static int count;
	//cout<<previous_time<<endl;
	if(sub.update==true)
	{
		sub.submarine_update();
		sub.update=false;
	}

	current_time=glutGet(GLUT_ELAPSED_TIME)/1000.0f;
	if(rad==false)
	{
		mytime=glutGet(GLUT_ELAPSED_TIME)/1000.0f;
		rad=true;
	}
	else
	{
		delta_time=float(current_time)-float(mytime);
		count++;
		if(delta_time>=1)
		{
			frame=count;
			count=0;
			rad=false;
		}
//		cout<<frame<<endl;
	}

	
	//previous_time=clock()/CLOCKS_PER_SEC;
	    //delta_time=(float(current_time)-float(previous_time));
		
		
	
	
	physics_lag+=(current_time-previous_time);
	AI_lag+=(current_time-previous_time);
	//cout<<AI_lag;
	while(physics_lag>physics_delta_time || AI_lag>AI_delta_time)
	{
		if (physics_lag - physics_delta_time > AI_lag - AI_delta_time)
		{
		fis.update_physics(sub);
		sub.submarine_physics_update();
		if(fis.is_diamond()==1)
	{
		//physics_update_whale();
	}
		if(fis.is_diamond()==1)
	{
	    fis.fish_surface_collision();
		fis.fish_floor_collision();
		{
        submarine_shark_collision();
		}

		int rad1=fis.fish_shark_collision(p_whale_x,p_whale_y,p_whale_z);
		if(rad1==0)
		{
			shark_target_fish=false;
		}
		}
		//glutPostRedisplay();
		

		sub.submarine_floor_collision();
		
		sub.submarine_surface_collision();
		  fis.collision_detection(sub.xPosition,sub.yPosition,sub.zPosition);
		//fis.fish_neighbour();
		float current_time1 = glutGet(GLUT_ELAPSED_TIME);
		
		float current_time2 = glutGet(GLUT_ELAPSED_TIME);
	//	cout<<current_time2-current_time1<<"   ";
		//cout<<physics_lag<<endl;
		physics_lag-=physics_delta_time;
		//cout<<".";
		
		}
		else
		{
			fis.update_fast_ai();
			//background_sound ();
			if(fis.is_diamond()==1)
	{
			if(fast_AI_ESCORT==true)
			{
			fast_AI_Whale();
			}
			else
			{
			fast_AI_whale3();
			}}
			//cout<<AI_lag<<endl;
		    AI_lag-=AI_delta_time;
		}
		
	}
	
		
	previous_time=current_time;
	//fis.fish_speed();
	glutPostRedisplay();

}

void fog_enable()
{

	float fog_color[4] = {sub.red, sub.green, sub.blue, 1.0};

    glEnable(GL_FOG);
 
    glFogi(GL_FOG_MODE, GL_LINEAR);

	glHint(GL_FOG_HINT, GL_DONT_CARE);

	glFogfv(GL_FOG_COLOR, fog_color);

	glFogf (GL_FOG_START, 0);

	glFogf (GL_FOG_END, culling_distance);

}

void fog_disable()
{   
	cout<<"fog_disable";
	glDisable(GL_FOG);
}

void whale_model()
{
	
	//glMatrixMode(GL_MODELVIEW);
	GLUquadricObj* Sphere;
	Sphere=gluNewQuadric();
	float theta=0;
	


if(v_whale_z<0)
		{
			theta = 3.14 + atan(v_whale_x/v_whale_z);
		}


		else if (v_whale_z>0 )
		{
			theta = atan(v_whale_x/v_whale_z);
		}


		else
		{
			if(v_whale_x>0)
			{
				theta= 3.14/2;
			}
			else if(v_whale_x<0)
			{
				theta = (3 * 3.14) / 2;
			}

	   }
		theta = (theta * 180) / 3.14;
		float r;
		r = sqrt(powf(v_whale_x,2)+powf(v_whale_z,2));

		float pi;
		if(v_whale_y!=0 && r>0)
		{
			pi=atan(v_whale_y/r);
		}


		else if(r==0)
		{
			if(p_whale_y>0)
			{
				pi=3.14/2;
			}

			else if(p_whale_y<0)
			{
				pi = (3.14 * 3)/2;
			}
		}

		pi = (pi * 180) / 3.14;
		
		
		submarine1 sub2;
        GLUquadricObj *Spher;
		Spher = gluNewQuadric();
		glPushMatrix();
		
		glTranslatef(p_whale_x, p_whale_y, p_whale_z);	// unneeded since default position is (0, 0, 0)
		/*glBegin(GL_LINES);
              glVertex3d(0, 0, 0);
              glVertex3d(vx[i], vy[i], vz[i]);
         glEnd();*/
		glRotatef(theta, 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
		glRotatef(pi, -1.0, 0.0, 0.0);
		 glScalef(7.0, 7.0, 7.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glRotatef(90, 0.0, 1.0, 0.0);
	    whale_body.draw();
		if(sphere==true)
		{
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glColor4f(sub2.red, sub2.green, sub2.blue, 0.2f);
		gluSphere(Spher,1, 10, 10);
 
		glDisable(GL_BLEND);
		}
		
		
	   glPopMatrix();
		
		}
	  
		
		 





	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

		  




void physics_update_whale()
{

	Vector3 fi(p_whale_x, p_whale_y, p_whale_z);
		 
		 
			
		 if(p_whale_x<1000)
		 {
			 pwx=p_whale_x;
		 
		 p_whale_x=p_whale_x+(v_whale_x*(1/PHYSICS_UPDATE_RATE));
		 }
		 else
		 {
			 pwx=p_whale_x;
	       p_whale_x = p_whale_x-(v_whale_x*(1/PHYSICS_UPDATE_RATE));
		 }
		 
		 	
		 if(p_whale_y<1000)
		 {
		 pwy=p_whale_y;
		 p_whale_y=p_whale_y+(v_whale_y*(1/PHYSICS_UPDATE_RATE));
		 }
		 else
		 {
		    pwy=p_whale_y;
	       p_whale_y = p_whale_y-(v_whale_y*(1/PHYSICS_UPDATE_RATE));

		 }

		 if(p_whale_z>-1000)
		 {
		  pwz=p_whale_z;
		 p_whale_z=p_whale_z+(v_whale_z*(1/PHYSICS_UPDATE_RATE));
		 }
		 else
		 {
		   pwz=p_whale_z;
	       p_whale_z = p_whale_z-(v_whale_z*(1/PHYSICS_UPDATE_RATE));

		 }
		 

		  

}







void fast_AI_Whale()
{
	Vector3 p(p_whale_x, p_whale_y, p_whale_z);
	Vector3 t(sub.xPosition+SHARK_ESCORT_DISTANCE,sub.yPosition,sub.zPosition); 
	Vector3 r;
	Vector3 S;
	Vector3 V(v_whale_x,v_whale_y,v_whale_z);
	r=t-p;
	float sclipped;
	float d= r.getNorm();

	
	if(d<SHARK_ARRIVAL_SLOW_DISTANCE)
	{

		sclipped=SHARK_MAX_SPEED*d/SHARK_ARRIVAL_SLOW_DISTANCE;
	}
	else
	{
		sclipped=SHARK_MAX_SPEED;
	}

	Vector3 D;
	D=r.getNormalized();
	D.x=D.x*sclipped;
	D.y=D.y*sclipped;
	D.z=D.z*sclipped;

	S=D-V;
	
	Vector3 F;
	float ma= SHARK_MASS/AI_delta_time;
	F.x= ma*S.x;
	F.y=ma*S.y;
	F.z=ma*S.z;
	float Fmax=SHARK_ACCELERATION*SHARK_MASS;


	float ft=F.getNorm();
	//cout<<ft<<endl;

	if (ft>(SHARK_ACCELERATION*SHARK_MASS))
	{
		F.x=(F.x*Fmax)/ft;
		F.y=(F.y*Fmax)/ft;
		F.z=(F.z*Fmax)/ft;

	}

	//cout<<F<<endl;
	Vector3 A;
	A.x=F.x/SHARK_MASS;
	A.y=F.y/SHARK_MASS;
	A.z=F.z/SHARK_MASS;

	Vector3 ti;
	ti.x=A.x*AI_delta_time;
	ti.y=A.y*AI_delta_time;
	ti.z=A.z*AI_delta_time;

	Vector3 z;
	z.x=V.x+ti.x;
	z.y=V.y+ti.y;
	z.z=V.z+ti.z;
	ft=z.getNorm();
	if (ft>(SHARK_MAX_SPEED))
	{
		z.x=(z.x*SHARK_MAX_SPEED)/ft;
		z.y=(z.y*SHARK_MAX_SPEED)/ft;
		z.z=(z.z*SHARK_MAX_SPEED)/ft;


	}
	
	v_whale_x=z.x;
	v_whale_y=z.y;
	v_whale_z=z.z;
	//cout<<v_whale_x<<"  "<<v_whale_y<<"  "<<v_whale_z<<endl;

}

void slow_AI_whale1()
{

	//cout<<"hii"<<endl;
	Vector3 whale(v_whale_x,v_whale_y,v_whale_z);
	Vector3 v2;
	Vector3 v3;
	float beta;
	int fish_id_closest=-99;
	Vector3 p(p_whale_x, p_whale_y, p_whale_z);
	float distance1=0;

	if(shark_target_fish==false)
	{
		//cout<<"hii";
		fish_id_closest=-99;
	for(int i=0;i<(fis.total_fish_return());i++)
	{   beta=10;
		v2.x= fis.x[i]-p_whale_x;
		v2.y= fis.y[i]-p_whale_y;
		v2.z= -fis.z[i]+p_whale_z;

		//cout<<v2<<endl;

		if(v2.isZero()==false && whale.isZero()==false)
		{
		beta = whale.dotProduct(v2);
		
		float multili= (whale.getNorm() * v2.getNorm());
		beta=acosf( beta/multili);
		
		//cout<<beta<<endl;
		}
		if(whale.isZero())
		{
			v_whale_x=0;
			v_whale_y=0;
			v_whale_z=0;
		
		}
		else if(v2.isZero())
		{
			v_whale_x=0;
			v_whale_y=0;
			v_whale_z=0;
		
		}
		else if(v2.getNorm()> SHARK_DETECT_FISH_RADIUS)
		{
			v_whale_x=0;
			v_whale_y=0;
			v_whale_z=0;
		

		}
		else if(beta>3.14/3)
		{
			v_whale_x=0;
			v_whale_y=0;
			v_whale_z=0;
		
		}

		else
		{

			//cout<<beta;
			if(fish_id_closest==-99)
		    {
			cout<<target_fish_no<<endl;
			fish_id_closest=i;
			target_fish_no=i;
			shark_target_fish=true;
			distance1=v2.getNorm();

		    }
			else
			{
				if(v2.getNorm()<distance1)
				{
					cout<<target_fish_no<<endl;
					fish_id_closest=i;
					target_fish_no=i;
					shark_target_fish=true;
			        distance1=v2.getNorm();
				}
			}
		}

		


	}}
	 
					
	    
	}

	
	
  void submarine_shark_collision()
   {

	   Vector3 ps(p_whale_x,p_whale_y,p_whale_z);
	   Vector3 subp(sub.xPosition,sub.yPosition,sub.zPosition);

	   if(ps.getDistance(subp)<22)
	   {
		   sub.xPosition=sub.psx;
		   sub.yPosition=sub.psy;
		   sub.zPosition=sub.psz;
		   p_whale_x=pwx;
		   p_whale_y=pwy;
		   p_whale_z=pwz;
	   }





   }


  void fast_AI_whale3()
  {

	  slow_AI_whale1();
	  Vector3 p(p_whale_x, p_whale_y, p_whale_z);
	  Vector3 t(fis.x[target_fish_no],fis.y[target_fish_no], fis.z[target_fish_no]); 

	  if(shark_target_fish==true)
	{
		//cout<<target_fish_no<<" "<<endl;
	
	Vector3 r;
	Vector3 S;
	Vector3 V(v_whale_x,v_whale_y,v_whale_z);
	t.x= fis.x[target_fish_no]+ (fis.vx[target_fish_no]*SHARK_PURSUIT_LOOK_AHEAD_FACTOR);
	t.y= fis.y[target_fish_no]+ (fis.vy[target_fish_no]*SHARK_PURSUIT_LOOK_AHEAD_FACTOR);
	t.z= fis.z[target_fish_no]+ (fis.vz[target_fish_no]*SHARK_PURSUIT_LOOK_AHEAD_FACTOR);
	r=t-p;
	
	float d= r.getNorm();

	
	

	Vector3 D;
	D=r.getNormalized();
	D.x=D.x*SHARK_ACCELERATION ;
	D.y=D.y*SHARK_ACCELERATION ;
	D.z=D.z*SHARK_ACCELERATION ;
	

	S=D-V;
	Vector3 F;
	float ma= SHARK_MASS/AI_delta_time;
	F.x= ma*S.x;
	F.y=ma*S.y;
	F.z=ma*S.z;
	float Fmax=SHARK_ACCELERATION*SHARK_MASS;


	float ft=F.getNorm();
	//cout<<ft<<endl;

	if (ft>(SHARK_ACCELERATION*SHARK_MASS))
	{
		F.x=(F.x*Fmax)/ft;
		F.y=(F.y*Fmax)/ft;
		F.z=(F.z*Fmax)/ft;

	}

	//cout<<F<<endl;
	Vector3 A;
	A.x=F.x/SHARK_MASS;
	A.y=F.y/SHARK_MASS;
	A.z=F.z/SHARK_MASS;

	Vector3 ti;
	ti.x=A.x*AI_delta_time;
	ti.y=A.y*AI_delta_time;
	ti.z=A.z*AI_delta_time;

	Vector3 z;
	z.x=V.x+ti.x;
	z.y=V.y+ti.y;
	z.z=V.z+ti.z;
	ft=z.getNorm();
	if (ft>(SHARK_MAX_SPEED))
	{
		z.x=(z.x*SHARK_MAX_SPEED)/ft;
		z.y=(z.y*SHARK_MAX_SPEED)/ft;
		z.z=(z.z*SHARK_MAX_SPEED)/ft;


	}
	
	v_whale_x=z.x;
	v_whale_y=z.y;
	v_whale_z=z.z;
	
	}





	  else
	  {
		  for(int m=0;m<fis.total_fish_return();m++)
		  {

			  int random_fish_position=rand()%fis.total_fish_return();

			  t.x=fis.x[random_fish_position]+(rand()%50);
			  if(t.x>1000)
			  {
				  fis.x[random_fish_position]-(rand()%50);
			  }

			  t.y=fis.y[random_fish_position]+(rand()%50);
			   if(t.y>1000)
			   {
			    t.y=fis.y[random_fish_position]-(rand()%50);
			   }
			  t.z=fis.z[random_fish_position]+(rand()%50);

			  if(t.z>1000)
			  {
			    t.z=fis.z[random_fish_position]-(rand()%50);
			  }


			  Vector3 r;
	Vector3 S;
	Vector3 V(v_whale_x+2,v_whale_y+2,v_whale_z+2);
	r=t-p;
	
	float d= r.getNorm();

	
	

	Vector3 D;
	D=r.getNormalized();
	D.x=D.x*SHARK_ACCELERATION ;
	D.y=D.y*SHARK_ACCELERATION ;
	D.z=D.z*SHARK_ACCELERATION ;
	

	S=D-V;
	Vector3 F;
	float ma= SHARK_MASS/AI_delta_time;
	F.x= ma*S.x;
	F.y=ma*S.y;
	F.z=ma*S.z;
	float Fmax=SHARK_ACCELERATION*SHARK_MASS;


	float ft=F.getNorm();
	//cout<<ft<<endl;

	if (ft>(SHARK_ACCELERATION*SHARK_MASS))
	{
		F.x=(F.x*Fmax)/ft;
		F.y=(F.y*Fmax)/ft;
		F.z=(F.z*Fmax)/ft;

	}

	//cout<<F<<endl;
	Vector3 A;
	A.x=F.x/SHARK_MASS;
	A.y=F.y/SHARK_MASS;
	A.z=F.z/SHARK_MASS;

	Vector3 ti;
	ti.x=A.x*AI_delta_time;
	ti.y=A.y*AI_delta_time;
	ti.z=A.z*AI_delta_time;

	Vector3 z;
	z.x=V.x+ti.x;
	z.y=V.y+ti.y;
	z.z=V.z+ti.z;
	ft=z.getNorm();
	if (ft>(SHARK_MAX_SPEED))
	{
		z.x=(z.x*SHARK_MAX_SPEED)/ft;
		z.y=(z.y*SHARK_MAX_SPEED)/ft;
		z.z=(z.z*SHARK_MAX_SPEED)/ft;


	}
	
	v_whale_x=z.x;
	v_whale_y=z.y;
	v_whale_z=z.z;
	
		     
		  
		  }

	  }

	  

  }
			
	//else
	//	{
	//		Vector3 target(fis.x[target_fish_no],fis.y[target_fish_no],fis.z[target_fish_no]);
	//		if(p.getDistance(target)>400)
	//		{
	//			
	//			shark_target_fish=false;
	//		}

	//		Vector3 p(p_whale_x, p_whale_y, p_whale_z);
	//Vector3 t(fis.x[target_fish_no],fis.y[target_fish_no], fis.z[target_fish_no]); 
	//Vector3 r;
	//Vector3 S;
	//Vector3 V(v_whale_x,v_whale_y,v_whale_z);
	//r=t-p;
	//
	//float d= r.getNorm();

	//
	//

	//Vector3 D;
	//D=r.getNormalized();
	//D.x=D.x*SHARK_ACCELERATION ;
	//D.y=D.y*SHARK_ACCELERATION ;
	//D.z=D.z*SHARK_ACCELERATION ;
	//

	//S=D-V;
	//Vector3 F;
	//float ma= SHARK_MASS/AI_delta_time;
	//F.x= ma*S.x;
	//F.y=ma*S.y;
	//F.z=ma*S.z;
	//float Fmax=SHARK_ACCELERATION*SHARK_MASS;


	//float ft=F.getNorm();
	////cout<<ft<<endl;

	//if (ft>(SHARK_ACCELERATION*SHARK_MASS))
	//{
	//	F.x=(F.x*Fmax)/ft;
	//	F.y=(F.y*Fmax)/ft;
	//	F.z=(F.z*Fmax)/ft;

	//}

	////cout<<F<<endl;
	//Vector3 A;
	//A.x=F.x/SHARK_MASS;
	//A.y=F.y/SHARK_MASS;
	//A.z=F.z/SHARK_MASS;

	//Vector3 ti;
	//ti.x=A.x*AI_delta_time;
	//ti.y=A.y*AI_delta_time;
	//ti.z=A.z*AI_delta_time;

	//Vector3 z;
	//z.x=V.x+ti.x;
	//z.y=V.y+ti.y;
	//z.z=V.z+ti.z;
	//ft=z.getNorm();
	//if (ft>(SHARK_MAX_SPEED))
	//{
	//	z.x=(z.x*SHARK_MAX_SPEED)/ft;
	//	z.y=(z.y*SHARK_MAX_SPEED)/ft;
	//	z.z=(z.z*SHARK_MAX_SPEED)/ft;


	//}
	//
	//v_whale_x=z.x;
	//v_whale_y=z.y;
	//v_whale_z=z.z;



	//	}

	//	if(fish_id_closest!=-99)
	//	{
	//		v_whale_x=0;
	//		v_whale_y=0;
	//		v_whale_z=0;
	//	}

	


























//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//void submarine()
//{
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	    
//		glTranslatef(sub.xPosition, sub.yPosition, sub.zPosition);	//Actually submarine moves but camera also moves so submarine remains constant.
//		glRotatef(angle_sub, 0.0, 1.0, 0.0);	
//		glScalef(0.01, 0.01, 0.01);		
//	                //Triangle, Shape of submarine
//	    glColor3f(0.2, 0.02, 0.02);
//		submarine_obj.draw();
//		//submarine_body.draw();
//		// size is 0.6
//		glEnd();
//	glPopMatrix();
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
////Color of background changes according to the depth
//void depth_background()
//{
//	depth_color=fabsf(sub.zPosition)/1000.0;          //just dividing depth.
//	
//	
//	//at the shore color is blue, and when we move inside color strart to become green and then black
//	
//	//printf("  %f",depth_color);
//	if(depth_color<0.5)                //as we move inside green color increases and blue color decreases
//	glClearColor(0.0, 0.105+depth_color, 0.8-depth_color, 1.0);    //
//	
//	if(depth_color>=0.5 && depth_color<0.9 )     //Here green color start decreasing towards black
//	{
//
//		glClearColor(0.0, (1.5-depth_color-0.3), 0.8-depth_color, 1.0);
//	}
//
//	if(depth_color>=0.9)             //here background becomes black
//	{
//		glClearColor(0.0, 1.1-depth_color, 0.0, 1.0);
//	}
//}
//
//
//void submarine_update()
//{
//	//float velocity=SUBMARINE_ENGINE_FORCE / SUBMARINE_MASS * 1/20;
//
//	vxs=vxs * cos(angle_sub);
//	vzs=vzs * sin(angle_sub);
//}
//
//void submarine_physics_update()
//{
//
//	vxs = vxs * pow(SUBMARINE_DRAG, physics_delta_time);
//	vys = vys * pow(SUBMARINE_DRAG, physics_delta_time);
//	vzs = vzs * pow(SUBMARINE_DRAG, physics_delta_time);
//	
//	vys = vys + SUBMARINE_GRAVITY * physics_delta_time + SUBMARINE_BUOYANT_FORCE / SUBMARINE_MASS * buoyancy * physics_delta_time;
//	if(sub.xPosition>0 && sub.xPosition<1000)
//	{
//	sub.xPosition= sub.xPosition+vxs* physics_delta_time;
//	}
//	sub.yPosition= sub.yPosition+vys * physics_delta_time;
//	
//	sub.zPosition= sub.zPosition +vzs* physics_delta_time;
//}
//
//void submarine_turn_rate()
//{
//	cout<<"hii";
//	 if (angle_sub>360)
//	 {
//		 angle_sub=0;
//	 }
//	 angle_sub=angle_sub+SUBMARINE_TURN_RATE * (1.0/20.0);
//
//	 submarine_update();
//	 submarine();
//	 
//	 cout<<angle_sub;
//}
//
//void submarine_turn_clockwise()
//{
//	//cout<<"hii";
//	 if (angle_sub<-360)
//	 {
//		 angle_sub=0;
//	 }
//	 angle_sub=angle_sub-SUBMARINE_TURN_RATE * (1.0/20.0);
//	 submarine_update();
//	 submarine();
//	 //cout<<angle_sub;
//}
//
//void submarine_horizontal_velocity()
//{
//	float velocity=SUBMARINE_ENGINE_FORCE / SUBMARINE_MASS * 1/20;
//	Vector3 unit_vector, radh(vxs,vys,vzs);
//	unit_vector = radh.getNormalized();
//    vxs= vxs + unit_vector.x *velocity;
//	vzs = vzs + unit_vector.z *velocity;
//	
//}

//void background_sound ()
// {
//	 
//	 alGetError();
//	 ALenum error;
//
//	  alGenBuffers(5, buffers);
//	//bool error;
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("alGenBuffers : %d", error);
// exit(1);
//}
//
//
//
//
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("FreedomDance.wav : %d", error);
//  // Delete Buffers
//  alDeleteBuffers(5, buffers);
//  exit(1);
//}   
//
//alBufferData(buffers[0],format,data,size,freq);
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("alBufferData buffer 0 : %d", error);
//  // Delete buffers
//  alDeleteBuffers(5, buffers);
//  exit(1);
//}
//
//alutUnloadWAV(format,data,size,freq);
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("alutUnloadWAV : %d", error);
//  // Delete buffers
//  alDeleteBuffers(5, buffers);
//  exit (1);
//}
//	 
//	 alGenSources(5, source);
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("alGenSources : %d", error);
//  exit(1);
//}
//
//alSourcei(source[0], AL_BUFFER, buffers[0]);
//if ((error = alGetError()) != AL_NO_ERROR)
//{
//  printf("alSourcei : %d", error);
//  exit(1);
//}
//
// ALfloat SourcePos[] = { 0, 0, 0 };
//
// 
//
//// Velocity of the source sound.
//
//ALfloat SourceVel[] = { 0, 0, 0 };
//
// 
//
//// Position of the Listener.
//
//ALfloat ListenerPos[] = { 0, 0, 0 };
//
// 
//
//// Velocity of the Listener.
//
//ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
//
// 
//
//// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
//
//// Also note that these should be units of '1'.
//
//ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
////ALvoid alSourcefv(ALuint source,ALenum pname,ALfloat *values);
//alSourcefv (source[0], AL_POSITION, SourcePos);
//alSourcefv (source[0], AL_VELOCITY, SourceVel);
////alSourcei(source[0],AL_BUFFER, buffers);
//alSourcei (source[0], AL_LOOPING,  AL_FALSE );
//	//Vector3 fina= vect.getRandomUnitVector();
////ALvoid alListenerfv(ALenum pname,ALfloat *values);
//
//
//alListenerfv(AL_POSITION,ListenerPos);
//alListenerfv(AL_VELOCITY,ListenerVel);
//alListenerfv(AL_ORIENTATION,ListenerOri);
//alSourcePlay(source[0]);
//
////alSourceStop(source[0]);
//
// }
//
// void playSound(){
// // alSourcei (source[0], AL_LOOPING,  AL_TRUE );
//  alSourcePlay(source[0]);
//}
//
// void loadSound(){
//  // Load pcm data into buffer
//	 alGenBuffers(5, buffers);
//	// alBufferData(buffers[0],format,data,size,freq);
//     alutLoadWAVFile(FILENAME, &format, &data, &size, &freq, &loop);
//	 alBufferData(buffers[0],format,data,size,freq);
//  // Create sound source (use buffer to fill source)
//	 alutUnloadWAV(format,data,size,freq);
//  alGenSources(5, source);
//  alSourcei(source[0], AL_BUFFER, buffers[0]);
//}
//void cleanUpSound(){
//  // Clean up sources and buffers
//  alDeleteSources(1, source);
//  alDeleteBuffers(1, buffers);
//}