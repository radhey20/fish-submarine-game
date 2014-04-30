#include "submarine1.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include "glut.h"
#include <iostream>
   /* srand, rand */
#include "Vector3.h"
#include "fish.h"
#include "sleep.h"
using namespace std;


 fish fi;
submarine1::submarine1()
{

	vxs=0;
	vys=0;
	vzs=0;
	submarine_update();
	buoyancy=0.8;
	
	horizontal_angle=vzs/vxs;
	update=false;
	angle_sub=0;
	physics_delta_time=(1/PHYSICS_UPDATE_RATE);
	AI_delta_time=(1/_FAST_AI_UPDATE_RATE);
	ai_slow_value=SLOW_AI_UPDATE_FRACTION;
	delta_time=0;
	yPosition =500.0;     //Initial Position is at the middle of the sea
    xPosition=500.0;      //Initial Position is at middle of the sea
    zPosition=-500;   
	red=0;
	green=0;
	blue=0;
	increase_value=0.1;
	buoyancy_rate=(SUBMARINE_BUOYANCY_MAX + SUBMARINE_BUOYANCY_MIN)/2;
    tilt_rate = (SUBMARINE_TILT_MIN + SUBMARINE_TILT_MAX)/2 ;
	interpolation_value=(SUBMARINE_BUOYANCY_MIN - SUBMARINE_BUOYANCY_MAX)/increase_value;
	tilt_value= (SUBMARINE_TILT_MIN - SUBMARINE_TILT_MAX)/interpolation_value;
	c_z=20.0f;
	c_x=20.0f;
	sphe=false;
	
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
void submarine1:: submarine(const ObjModel &submarine_obj)
{
	glMatrixMode(GL_MODELVIEW);
	GLUquadricObj* Sphere;
	Sphere=gluNewQuadric();
	glPushMatrix();

		glTranslatef(xPosition, yPosition, zPosition);	//Actually submarine moves but camera also moves so submarine remains constant.
		glRotatef(angle_sub, 0.0, 1.0, 0.0);	
		glRotatef(tilt_rate, -1.0, 0.0, 0.0);
		//cout<<tilt_rate<<"  ";
		glRotatef(-90,0,1,0);
		//glScalef(0.02, 0.02, 0.02);		
		  
	      glColor3f(1.0, 1.0, 1.0);
		  submarine_obj.draw();

		  if(sphe==true)
		  {
		  glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		  
		  glColor4f(red, green, blue, 0.3f);
		  glPushMatrix();
		  glTranslatef(-9, 0, 0);
          gluSphere(Sphere,SUBMARINE_SPHERE_RADIUS, 10, 10);
		  glTranslatef(4.5, 0, 0);
		  gluSphere(Sphere,SUBMARINE_SPHERE_RADIUS, 10, 10);
		  glTranslatef(4.5, 0, 0);
		  gluSphere(Sphere,SUBMARINE_SPHERE_RADIUS, 10, 10);
		  glTranslatef(4.5, 0, 0);
		  gluSphere(Sphere,SUBMARINE_SPHERE_RADIUS, 10, 10);
		  glTranslatef(4.5, 0, 0);
		  gluSphere(Sphere,SUBMARINE_SPHERE_RADIUS, 10, 10);
		 // glTranslatef(4.5, 0, 0);
		  glPopMatrix();
          glColor4f(red, green, blue, 0.1f);
          gluSphere(Sphere,SUBMARINE_OUTER_RADIUS, 50, 50);
 
          glDisable(GL_BLEND);
		  }

	glPopMatrix();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
//Color of background changes according to the depth
void submarine1:: depth_background()
{
	depth_color=fabsf(zPosition)/1000.0;          //just dividing depth.
	
	
	//at the shore color is blue, and when we move inside color strart to become green and then black
	
	//printf("  %f",depth_color);
	//if(depth_color<0.5)                //as we move inside green color increases and blue color decreases
	
	red=0.1;
	green= 0.8-depth_color;
	blue=  0.105+depth_color;

	    //glClearColor(0.0, 0.105+depth_color, 0.8-depth_color, 1.0);  //
	
	
	//if(depth_color>=0.5)     //Here green color start decreasing towards black
	//{
	//	red=0.0;
	//    green= 0.3-depth_color-0.3;
	//    blue= 0.8-depth_color;
	//	//glClearColor(0.0, (1.5-depth_color-0.3), 0.8-depth_color, 1.0);
	//}

	
	glClearColor(red, green, blue, 1.0);
	//cout<<red<<"  "<<blue<<"  "<<green <<endl;
}



void submarine1:: submarine_update()
{
	//float velocity=SUBMARINE_ENGINE_FORCE / SUBMARINE_MASS * 1/20;

	//vxs=vxs * cos(angle_sub);
	//vzs=vzs * sin(angle_sub);
}


void submarine1:: submarine_physics_update()
{
	 static int count;
	 
	
	 if(yPosition>1000)
	 {
		 
		 //cout<<"hii";
		 if(count==0)
		 {
			
			 xPosition=500.0;
		     yPosition=1500.0;
		     zPosition=-500.0;
			 //cout<<subs.yPosition<<endl;
			 count=1;
		 }
	 }
	 else
	 {

		 
		  if(count==1)
		 {
			
			 count=0;
		 }
		
	 }
	
	
	psx=xPosition;
	psy=yPosition;
	psz=zPosition;
	vxs = vxs * pow(SUBMARINE_DRAG, physics_delta_time);
	vys = vys * pow(SUBMARINE_DRAG, physics_delta_time);
	vzs = vzs * pow(SUBMARINE_DRAG, physics_delta_time);
	
	vys = vys + SUBMARINE_GRAVITY * physics_delta_time + SUBMARINE_BUOYANT_FORCE / SUBMARINE_MASS * buoyancy * physics_delta_time;
	
	
	xPosition= xPosition+ vxs* physics_delta_time;
	
	yPosition= yPosition+ vys * physics_delta_time;
	
	zPosition= zPosition + (vzs* physics_delta_time);

	
	//cout<<xPosition<<"  "<<yPosition<<"  "<<zPosition<<endl;
}


void submarine1:: submarine_turn_rate()
{
	//cout<<"hii";
	 if (angle_sub>360)
	 {
		 angle_sub=0;
	 }
	 angle_sub=angle_sub+SUBMARINE_TURN_RATE * (1.0/20.0);

	 submarine_update();
//	 submarine();
	 
	// cout << angle_sub;
}


void submarine1:: submarine_turn_clockwise()
{
	//cout<<"hii";
	 if (angle_sub<-360)
	 {
		 angle_sub=0;
	 }
	 angle_sub=angle_sub-SUBMARINE_TURN_RATE * (1.0/20.0);
	 submarine_update();
	// submarine();
	 //cout<<angle_sub;
}


void submarine1:: submarine_horizontal_velocity()
{
	float velocity_change=SUBMARINE_ENGINE_FORCE / SUBMARINE_MASS * 1.0/20.0;
	float angle_in_radians = angle_sub * 3.1415926 / 180.0;
	Vector3 unit_vector(sin(angle_in_radians), 0, cos(angle_in_radians));
    vxs= vxs + unit_vector.x *velocity_change;
	vzs = vzs + unit_vector.z *velocity_change;
	
}


void submarine1::submarine_decreasing_velocity()
{
	
	float velocity_change=SUBMARINE_ENGINE_FORCE / SUBMARINE_MASS * 1.0/20.0;
	float angle_in_radians = angle_sub * 3.1415926 / 180.0;
	Vector3 unit_vector(sin(angle_in_radians), 0, cos(angle_in_radians));
	
	
	
    vxs= vxs - unit_vector.x *velocity_change;
	vzs = vzs - unit_vector.z *velocity_change;
	
}



void submarine1:: buoyancy_increase()
{
	if(buoyancy_rate < SUBMARINE_BUOYANCY_MAX)
	 {
		  buoyancy_rate+=0.1;
		  tilt_rate+=tilt_value;
	  
	  }
}


void submarine1:: buoyancy_decrease()
{
	if(buoyancy_rate > SUBMARINE_BUOYANCY_MIN)
	 {
		  buoyancy_rate-=0.1;
		  tilt_rate-=tilt_value;
	      
	  }
}

void submarine1:: submarine_surface_collision()
{
	/*if(yPosition+SUBMARINE_OUTER_RADIUS>1000)
	   {
		   xPosition=psx;
		   yPosition=psy;
		   zPosition=psz;
		   vys=-vys;
	   }*/

	  // if(yPosition+9<=4)
	  // {
		 //  xPosition=psx;
		 //  yPosition=psy;
		 //  zPosition=psz;
		 //  vys=-vys;
		 ////  cout<<psx<<" "<<psy<<" "<<psz<<endl;
	  // }

	   if(xPosition+SUBMARINE_OUTER_RADIUS<3)
       {
		  xPosition=psx;
		   yPosition=psy;
		   zPosition=psz;
		   vxs=-vxs;
	   }

	   if(xPosition+SUBMARINE_OUTER_RADIUS>1000)
       {
		   xPosition=psx;
		   yPosition=psy;
		   zPosition=psz;
		   vxs=-vxs;
	   }
	    if(zPosition+SUBMARINE_OUTER_RADIUS<-1000)
		{

		   xPosition=psx;
		   yPosition=psy;
		   zPosition=psz;
		   vzs=-vzs;
		}
		 if(zPosition+SUBMARINE_OUTER_RADIUS>0)
		{

		   xPosition=psx;
		   yPosition=psy;
		   zPosition=psz;
		   vzs=-vzs;
		}

		  if(yPosition+SUBMARINE_OUTER_RADIUS>2000)
		{

		   xPosition=psx;
		   yPosition=1900;
		   zPosition=psz;
		   
		}


	 }

   
   void submarine1:: submarine_floor_collision()
   {
	   q_k= ((-1.0*zPosition)/c_z);
	   q_i = (xPosition/c_x);

	  
	   float f_k= q_k-floor(q_k);
	   float f_i= q_i-floor(q_i);
	   Vector3 N;

	   
	    //cout<<f_k<<"  "<<f_i<<"  ";
	   
	    
	   int k=floor(q_k);
	   int i=floor(q_i);
	   Vector3 P01;

	   if(f_k + f_i < 1)
	   {
		   
	   Vector3 P0( (i*c_x), fi.fy[i][k],  k*c_z);
	   Vector3 P1( i*c_x, fi.fy[i+1][k],  (k+1)*c_z);
	   Vector3 P2((i+1)*c_x, fi.fy[i][k+1], k*c_z);
	   Vector3 P3=(P1-P0);
	   Vector3 P4=(P2-P0);
	 //  P3.z=-P3.z;
	   //P4.z=-P4.z;

	  // cout<<P0<<"  "<<P1<<"  "<<P2<<"  "<<P3<<endl;
	   P01=P0;
	   N=P3.crossProduct(P4);



	   }

	   else
	   {
		   
	   Vector3 P0( (i+1)*c_x, fi.fy[i+1][k+1], (k+1)*c_z);  
	   Vector3 P1( i*c_x, fi.fy[i+1][k], (k+1)*c_z);  
	   Vector3 P2((i+1)*c_x, fi.fy[i][k+1], k*c_z);  
	   Vector3 P3=(P2-P0);   
	   Vector3 P4=(P1-P0);  
	   N=P3.crossProduct(P4);  
	   P01=P0;    

	  

	   }

	   

	   double dot_pro = N.dotProduct(P01);
	   double yax= (((-N.x * xPosition)-(N.z*(-zPosition))+dot_pro)/N.y);
	//  cout<<yax<<"  ";

	   if((yPosition-15) < yax)
	   {

		//   cout<<vxs<<"  "<<vys<<"  "<<vzs;
		   Vector3 Velocity(vxs,vys,vzs);

		    

		    Velocity=Velocity - (2.0 * (Velocity.projection(N)));
		    vxs=Velocity.x;
	        vys=Velocity.y;
	        vzs=-Velocity.z;

			
			if((yPosition-5) < yax)
			{
				yPosition+=5;
			}


	   }
	  

   }

   

   void submarine1::skybox(submarine1 subs)
   {
       
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glColor4f(1,1,1,1);
     glEnable(GL_TEXTURE_2D);
	TextureManager::activate("sky_box3.bmp");
	//glClearColor(0.0, 0.0, 0.0, 0.0); 
//glEnable(GL_DEPTH_TEST);
//
	//glClear(GL_COLOR_BUFFER_BIT);

//glClearDepth(1);
//S is the side length of the cube
float s = 5;
//glShadeModel(GL_SMOOTH);
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//glHint(GL_POLYGON_SMOOTH, GL_NICEST);
//glTranslatef(subs.xPosition-500,subs.yPosition-1500, subs.zPosition+1500);
//glEnable(GL_POLYGON_SMOOTH);
	//glBindTexture( GL_TEXTURE_2D,   );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glPushMatrix();
   
	// GLuint skybox[6];

	// glBindTexture(GL_TEXTURE_2D, skybox[0]);
//	glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
	//front
	 glBegin(GL_QUADS);

       glTexCoord2f(0.25, 0.333333); glVertex3f(   1000, 1000, 0 );
       glTexCoord2f(0.50, 0.333333); glVertex3f(    0,   1000, 0 );
       glTexCoord2f(0.50, 0.666666); glVertex3f(   0,   2000, 0 );
       glTexCoord2f(0.25, 0.666666); glVertex3f(  1000,  2000, 0 );
   glEnd();
   // glDisable(GL_TEXTURE_2D);
   glPopMatrix();


    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glPushMatrix();
  // glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
    //glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	// left
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.333333); glVertex3f(  1000, 1000, -1000 );
       glTexCoord2f(0.25, 0.333333); glVertex3f(  1000, 1000, 0 );
       glTexCoord2f(0.25, 0.666666); glVertex3f(  1000, 2000, 0 );
       glTexCoord2f(0.0,0.666666); glVertex3f(  1000, 2000, -1000 );
   glEnd();
    //glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   //back
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glPushMatrix();
	   //glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
    //glEnable(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	

	 //glBindTexture(GL_TEXTURE_2D, skybox[2]);

	
    //back
	
	 glBegin(GL_QUADS);
       glTexCoord2f(0.75,0.333333); glVertex3f(  0,    1000, -1000 );
       glTexCoord2f(1.0, 0.333333); glVertex3f(  1000, 1000,  -1000 );
       glTexCoord2f(1.0, 0.666666); glVertex3f(  1000, 2000, -1000 );
       glTexCoord2f(0.75, 0.666666); glVertex3f(  0,   2000, -1000);
   glEnd();
    //glDisable(GL_TEXTURE_2D);
   glPopMatrix();

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glPushMatrix();
  // glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
    //glEnable(GL_TEXTURE_2D);
	 glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   // TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[3]);
	//right
	 glBegin(GL_QUADS);
       glTexCoord2f(0.50, 0.333333); glVertex3f(  0,  1000, 0 );
       glTexCoord2f(0.75, 0.333333); glVertex3f(  0,  1000, -1000 );
       glTexCoord2f(0.75, 0.666666); glVertex3f(  0, 2000, -1000);
       glTexCoord2f(0.50, 0.666666); glVertex3f(  0, 2000, 0 );
   glEnd();
   // glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glPushMatrix();
  // glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
    glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //  TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	//top
	 glBegin(GL_QUADS);
       glTexCoord2f(0.50, 0.666666); glVertex3f(  0, 2000, 0 );
       glTexCoord2f(0.50, 1.0); glVertex3f(  0, 2000, -1000 );
       glTexCoord2f(0.25, 1.0); glVertex3f(  1000, 2000, -1000 );
       glTexCoord2f(0.25, 0.666666); glVertex3f(  1000, 2000, 0 );
   glEnd();
    //glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glPushMatrix();
   //glTranslatef(subs.xPosition-500,subs.yPosition-1500, -1500-subs.zPosition);
    glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	//bottom
	 glBegin(GL_QUADS);
       glTexCoord2f(0.50, 0.34); glVertex3f( 0, 1000, 0 );
       glTexCoord2f(0.50,0.0); glVertex3f(  0, 1000,  -1000);
       glTexCoord2f(0.25, 0.0); glVertex3f(  1000, 1000,-1000 );
       glTexCoord2f(0.25, 0.34); glVertex3f( 1000, 1000, 0 );
   glEnd();
    glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glEnable(GL_DEPTH_TEST);
   
   }




   void submarine1::skybox1()
   {
       
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glColor4f(1,1,1,1);
     glEnable(GL_TEXTURE_2D);
	
	//glClearColor(0.0, 0.0, 0.0, 0.0); 
//glEnable(GL_DEPTH_TEST);
//
	//glClear(GL_COLOR_BUFFER_BIT);

//glClearDepth(1);
//S is the side length of the cube
float s = 5;
//glShadeModel(GL_SMOOTH);
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//glHint(GL_POLYGON_SMOOTH, GL_NICEST);

//glEnable(GL_POLYGON_SMOOTH);
	//glBindTexture( GL_TEXTURE_2D,   );
    TextureManager::activate("front.bmp");
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glPushMatrix();
   
	// GLuint skybox[6];

	// glBindTexture(GL_TEXTURE_2D, skybox[0]);

	//front
	 glBegin(GL_QUADS);

       glTexCoord2f(0.0, 0.0); glVertex3f(   1000, 1000, 0 );
       glTexCoord2f(1.0, 0.0); glVertex3f(    0,   1000, 0 );
       glTexCoord2f(1.0, 1.0); glVertex3f(   0,   2000, 0 );
       glTexCoord2f(0.0, 1.0); glVertex3f(  1000, 2000, 0 );
   glEnd();
   // glDisable(GL_TEXTURE_2D);
   glPopMatrix();

    TextureManager::activate("left.bmp");
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	// left
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0); glVertex3f(  1000, 1000, -1000 );
       glTexCoord2f(1.0, 0.0); glVertex3f(  1000, 1000, 0 );
       glTexCoord2f(1.0, 1.0); glVertex3f(  1000, 2000, 0 );
       glTexCoord2f(0.0,1.0); glVertex3f(  1000, 2000, -1000 );
   glEnd();
    //glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   //back

    TextureManager::activate("back.bmp");
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	
   glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	

	 //glBindTexture(GL_TEXTURE_2D, skybox[2]);

	
    //back
	
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0,0.0); glVertex3f(  0,    1000, -1000 );
       glTexCoord2f(1.0, 0.0); glVertex3f(  1000, 1000,  -1000 );
       glTexCoord2f(1.0, 1.0); glVertex3f(  1000, 2000, -1000 );
       glTexCoord2f(0.0, 1.0); glVertex3f(  0,    2000, -1000 );
   glEnd();
    //glDisable(GL_TEXTURE_2D);

   glPopMatrix();

    TextureManager::activate("right.bmp");
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	
   glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
	 
   // TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[3]);
	//right
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);  glVertex3f(  0,  1000, 0 );
       glTexCoord2f(1.0, 0.0);  glVertex3f(  0,  1000, -1000 );
       glTexCoord2f(1.0, 1.0);  glVertex3f(  0, 2000, -1000 );
       glTexCoord2f(0.0, 1.0);  glVertex3f(  0, 2000, 0 );
   glEnd();
   // glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	 TextureManager::activate("up.bmp");
   glPushMatrix();
  //  glEnable(GL_TEXTURE_2D);
	
  //  TextureManager::activate("seafloor.bmp");
	

	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	//top
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0); glVertex3f(  0, 2000, 0 );
       glTexCoord2f(1.0, 0.0); glVertex3f(  0, 2000, -1000 );
       glTexCoord2f(1.0, 1.0); glVertex3f(  1000, 2000, -1000 );
       glTexCoord2f(0.0, 1.0); glVertex3f(  1000, 2000, 0 );
   glEnd();
    //glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glPushMatrix();
   // glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //TextureManager::activate("seafloor.bmp");
	 
	TextureManager::activate("down.bmp");
	// glBindTexture(GL_TEXTURE_2D, skybox[1]);
	//bottom
	 glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0); glVertex3f( 0, 1000, 0 );
       glTexCoord2f(1.0,0.0); glVertex3f(  0, 1000,  -1000);
       glTexCoord2f(1.0, 1.0); glVertex3f(  1000, 1000,-1000 );
       glTexCoord2f(0.0, 1.0); glVertex3f( 1000, 1000, 0 );
   glEnd();
    glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   glEnable(GL_DEPTH_TEST);
   
   }