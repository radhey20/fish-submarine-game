// Name Radhey Shah, Id:200333585, 
//Assignment-1, CS-409



#include "fish.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include "glut.h"
#include <iostream>
#include <math.h>
   
#include "Vector3.h"
#include "submarine1.h"

using namespace std;

int total_fish;
int score;
submarine1 sub1;
ALuint source[5];
ALenum     format;
ALsizei    size;
ALsizei    freq;
ALboolean  loop;
ALvoid*    data;
ALuint buffers[5];
static int shouldPlaySound1=1;
fish::fish()
{

  Vector3 fina;
  float depth_color;
  ifstream inFile;
  sub_inside=true;
  score=0;
  theta=0;
  pi=0;
  c_z=20.0f;
  c_x=20.0f;
  is_culling=false;
  counter=0;
  srand(time(NULL));
  total_fish=(rand()%100)+201;   //randomly generate the number of fish between 100 and 200
 
      for(int i=0;i<2000;i++)
      {
          x[i]=(rand()%1000)+1;         //Randomly assign x,y, and z to each fish;
          y[i]=(rand()%1000)+1;
          z[i]=-((rand()%1000)+1);

          Vector3 vect(x[i],y[i],z[i]);
          Vector3 desire;


          fina=vect.getRandomUnitVector();
          vx[i]=fina.x * FISH_SPEED_MAX;
          vy[i]=fina.y * FISH_SPEED_MAX;
          vz[i]=fina.z * FISH_SPEED_MAX;

          dx[i]=fina.x * FISH_SPEED_MAX;
          dy[i]=fina.y * FISH_SPEED_MAX;
          dz[i]=fina.z * FISH_SPEED_MAX;
          slow_ai=SLOW_AI_UPDATE_FRACTION;


          if(i<(0.4*total_fish))
          {
	          diamond[i]=1;
          }
		   
         else
          {
	         diamond[i]=1;
          }


         depth_color=fabsf(z[i]);       //randomly give the color to the fish from red to green to light colors

         if(depth_color<=0.3)          //color of fish will be also according to depth, 
         {
             red[i]=((rand()%255)+1)/255.0; //background at this depth is blue, so just make sure that fish is not blue
             green[i]=((rand()%255)+1)/255.0;
             blue[i]=0;

         }


         else if(depth_color>0.3 || depth_color<=0.7)//background is green so making sure that fish is not green
         {
	        red[i]=((rand()%255)+1)/255.0;
            green[i]=0;
            blue[i]=((rand()%255)+1)/255.0;
         }


        else                          //background is very dark so making sure that fish has light color
        {
	       red[i]=(rand()%(255-150+1)+150)/255.0;
           green[i]=((rand()%255)+1)/255.0;
           blue[i]=((rand()%255)+1)/255.0;
        }

        is_there=false;
//cout<<red[i]<<"  "<<green[i]<<"  "<<blue[i]<<endl;
     }




    for(int g=0; g<100;g++)
    {

	    for(int t=0;t<100;t++)
	    {
		   fx[g][t]=0;
		   fy[g][t]=0;
		   fz[g][t]=0;
		   fu[g][t]=0;
		   fv[g][t]=0;
	   }

   }



	inFile.open("Heightmap.txt",ios ::in);

	if (!inFile)
	{
		cout<<"Unable to open"<<endl;
		exit(1);
	}
	 float file;
	inFile>>file;
	inFile>>file;

	 for(int i=0; i<=55; i++)
	 {

		 for(int j=0;j<=55;j++)
		 {  
			 if(j>=50)
		 {
			 fx[i][j]=j*20;
			 fy[i][j]=fy[i][0];
			 fz[i][j]=i*20;
		 }
			 else if(i>=50)
			{
				fx[i][j]=j*20;
			    fy[i][j]=fy[0][j];
			    fz[i][j]=i*20;
			 }
			 else
			 {
			 inFile>>file;
			 fx[i][j]=j*20;
			 fy[i][j]=file;
			 fz[i][j]=i*20;
			 }
			
		 }
		
		 
	 }


	 sphere=false;

	






}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fish::fish_position_color(ObjModel spiky_obj)  // cube is represented as fish
{
	
	 
    
	
	for(int i=0;i<total_fish;i++)
	{ //  glColor3f(red[i], blue[i], green[i]);

		
		Vector3 fi(x[i], y[i], z[i]);
		Vector3 su(sub1.xPosition, sub1.yPosition, sub1.zPosition);

	//cout<<sub1.xPosition<< sub1.yPosition<< sub1.zPosition;
		 if(su.getDistance(fi)<150)
		 {


	    if(vz[i]<0)
		{
			theta = 3.14 + atan(vx[i]/vz[i]);
		}


		else if (vz[i]>0 )
		{
			theta = atan(vx[i]/vz[i]);
		}


		else
		{
			if(vx[i]>0)
			{
				theta= 3.14/2;
			}
			else if(vx[i]<0)
			{
				theta = (3 * 3.14) / 2;
			}

	   }
		theta = (theta * 180) / 3.14;

		r = sqrt(powf(vx[i],2)+powf(vz[i],2));


		if(vy[i]!=0 && r>0)
		{
			pi=atan(vy[i]/r);
		}


		else if(r==0)
		{
			if(y>0)
			{
				pi=3.14/2;
			}

			else if(y<0)
			{
				pi = (3.14 * 3)/2;
			}
		}

		pi = (pi * 180) / 3.14;
		
		
		submarine1 sub;
        GLUquadricObj *Spher;
		Spher = gluNewQuadric();
		glPushMatrix();
		
		glTranslatef(x[i], y[i], z[i]);	// unneeded since default position is (0, 0, 0)
		/*glBegin(GL_LINES);
              glVertex3d(0, 0, 0);
              glVertex3d(vx[i], vy[i], vz[i]);
         glEnd();*/
		glRotatef(theta, 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
		glRotatef(pi, -1.0, 0.0, 0.0);
		glScalef(15.0, 15.0, 15.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glRotatef(90, 0.0, 1.0, 0.0);
	    spiky_obj.draw();		// size is 0.6

		if(sphere==true)
		{
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glColor4f(sub.red, sub.green, sub.blue, 0.2f);
		gluSphere(Spher,1, 10, 10);
 
		glDisable(GL_BLEND);
		}
	    glPopMatrix();
		
		 }
		 else
		 {

               if(vz[i]<0)
		{
			theta = 3.14 + atan(vx[i]/vz[i]);
		}


		else if (vz[i]>0 )
		{
			theta = atan(vx[i]/vz[i]);
		}


		else
		{
			if(vx[i]>0)
			{
				theta= 3.14/2;
			}
			else if(vx[i]<0)
			{
				theta = (3 * 3.14) / 2;
			}

	   }
		theta = (theta * 180) / 3.14;

		r = sqrt(powf(vx[i],2)+powf(vz[i],2));


		if(vy[i]!=0 && r>0)
		{
			pi=atan(vy[i]/r);
		}


		else if(r==0)
		{
			if(y>0)
			{
				pi=3.14/2;
			}

			else if(y<0)
			{
				pi = (3.14 * 3)/2;
			}
		}

		pi = (pi * 180) / 3.14;
		
		
		submarine1 sub;
        GLUquadricObj *Spher;
		Spher = gluNewQuadric();
		glPushMatrix();
		
		glTranslatef(x[i], y[i], z[i]);	// unneeded since default position is (0, 0, 0)
		/*glBegin(GL_LINES);
              glVertex3d(0, 0, 0);
              glVertex3d(vx[i], vy[i], vz[i]);
         glEnd();*/
		glRotatef(theta, 0.0, 1.0, 0.0);	// unneeded since default rotation is 0 degrees
		glRotatef(pi, -1.0, 0.0, 0.0);
		glScalef(5.0, 5.0, 5.0);		// unneeded since default scaling is 1 in X, Y, and Z
		glRotatef(90, 0.0, 1.0, 0.0);
	    spiky_obj.draw();		// size is 0.6

		if(sphere==true)
		{
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glColor4f(sub.red, sub.green, sub.blue, 0.2f);
		gluSphere(Spher,1, 10, 10);
 
		glDisable(GL_BLEND);
		}
	    glPopMatrix();








		 }
	
	



}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

int fish::no_fish()
{
	return(total_fish);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
void fish::collision_detection(float xPosition,int yPosition,int zPosition)
{
	float distance;
	int scor;
	 double time_counter = 0;
	clock_t this_time ;
    clock_t last_time ;
    static clock_t store_time ;

        
	
	for(int i=0;i<total_fish;i++)
	{


		//if(is_there==true)
		//{
		//	
		//	if(counter==0)
		//	{   this_time=clock();
		//		store_time = this_time;
		//		counter=1;
		//	}


		//   last_time=clock();
		//   time_counter += (double)(last_time-store_time);

  //          if(time_counter < (double)(3000 * CLOCKS_PER_SEC))
  //          {
  //          
  //          
		//	
		//	if(zPosition-z[i]<10000)      //just making sure that z position is close enough and then check x and y position.
		//    {
		//        distance=((powf(xPosition-x[i],2))+(powf(yPosition-y[i],2)));

		//        if(distance<500)
		//        {
		//	         is_there=invisible_fish(i);
		//        }

		//   }
		//	
		//   }

		//	else
		//	{
		//		
		//		counter=0;
		//		is_there=false;
		//	}
		//}







		

		//distance=sqrt(((powf((x[i]+5)-(xPosition+ SUBMARINE_SPHERE_MAX_DISTANCE ),2))+(powf((y[i]+5)-(yPosition+ SUBMARINE_SPHERE_MAX_DISTANCE) ,2))+(powf((z[i]+5)-(zPosition+ SUBMARINE_SPHERE_MAX_DISTANCE) ,2))));
		

		distance=(((powf((x[i])-(xPosition ),2))+(powf((y[i])-(yPosition) ,2))+(powf((z[i])-(zPosition) ,2))));
		
		//cout<<distance<<"  ";
		if(distance<196)
		{    cout<<endl;
			//is_there=invisible_fish(i);
			float count=-9.0;
			for(int j=0;j<5;j++)
			{

			distance= ((powf(((x[i])-(xPosition)),2))+(powf(((y[i])-(yPosition)) ,2))+(powf(((z[i])-(zPosition+count)) ,2)));
		  
			//cout<<distance<<"  "<<endl;
			if(distance<64)

			{

				is_there=invisible_fish(i);
				break;
			}
			//cout<<count<<endl;;
			count=count+4.5;
			}
			
		}


		
		

	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
 bool fish::invisible_fish(int i)
{
	x[i]=x[total_fish]; 
	y[i]=y[total_fish];
	z[i]=z[total_fish];
	red[i]=red[total_fish];
	blue[i]=blue[total_fish];
	green[i]=green[total_fish];
	total_fish=total_fish-1;
	score=score+10;
	catching_sound();
	if(diamond[i]==1)
	{
		return(1);
	}

	

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 bool fish::is_finish()
 {
	 if(score>=100)
	 {
		 return(true);
	 }

	 else
	 {
		 return(false);
	 }
 }

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int fish::my_score()
 {
	 return(score);
 }
 int fish:: is_diamond()
{
	return(is_there);
}

 

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void fish::update_physics(submarine1 subs)
 {
	//cout<<"physics update"<<endl;
	 static int count;
	 
	
	 if(subs.yPosition>1000)
	 {
		 sub_inside=false;
		 //cout<<"hii";
		 if(count==0)
		 {
			 for(int i=0;i<total_fish;i++)
			 {
		  x[i]=(rand()%1000)+1;         //Randomly assign x,y, and z to each fish;
          y[i]=(rand()%1000)+1000;
          z[i]=-((rand()%1000)+1);
		  
			 }

			 subs.xPosition=500.0;
		     subs.yPosition=1500.0;
		     subs.zPosition=-500.0;
			 cout<<subs.yPosition<<endl;
			 count=1;
		 }
	 }
	 else
	 {

		 sub_inside=true;
		  if(count==1)
		 {
			 for(int i=0;i<total_fish;i++)
			 {
		  x[i]=(rand()%1000)+1;         //Randomly assign x,y, and z to each fish;
          y[i]=(rand()%1000)+1;
          z[i]=-((rand()%1000)+1);
			 }
			 count=0;
		 }
		
	 }
	 
	 static int count_x=0;
	 static int count_y=0;
	 static int count_z=0;
	 for(int i=0;i<total_fish;i++)
	 {
		 px[i]=x[i];
		 py[i]=y[i];
		 pz[i]=z[i];

		 Vector3 fi(x[i], y[i], z[i]);
		 Vector3 su(sub1.xPosition, sub1.yPosition, sub1.zPosition);
		 if(is_culling==true)
		 {
		 if(su.getDistance(fi)<culling_distance)
		 {
			// cout<<su.getNorm()-fi.getNorm()<<endl;
		 if(x[i]<980 && count_x==0)
		 {
			 
		 x[i]=x[i]+(vx[i]*(1/PHYSICS_UPDATE_RATE));
		 }
		 else
		 {
			count_x=1;
	    x[i]=x[i]-(vx[i]*(1/PHYSICS_UPDATE_RATE));
		 if(x[i]<30)
			 {
				 count_x=0;
			 }
		 }

		 if(sub_inside==true)
		 {
		  if(y[i]<980 && count_y)
		  {
			   
		       y[i]=y[i]+vy[i]*(1/PHYSICS_UPDATE_RATE);
		  }
		  else
		  {    count_y=1;
			   y[i]=y[i]-vy[i]*(1/PHYSICS_UPDATE_RATE);
			   if(y[i]<30)
			 {
				 count_y=0;
			 }
		  }
		  
		 }
		 else
		 {
			  if(y[i]<1980 && count_y)
		  {
			   
		       y[i]=y[i]+vy[i]*(1/PHYSICS_UPDATE_RATE);
		  }
		  else
		  {    count_y=1;
			   y[i]=y[i]-vy[i]*(1/PHYSICS_UPDATE_RATE);
			   if(y[i]<30)
			 {
				 count_y=0;
			 }
		  }
		  
		 }

		  if(z[i]>-980 && count_z==0)
		  {
		 z[i]=z[i]+vz[i]*(1/PHYSICS_UPDATE_RATE);
		  }
		  else
		  {       
			  count_z=1;
			   z[i]=z[i]-vz[i]*(1/PHYSICS_UPDATE_RATE);
			   if(z[i]>-30)
			 {
				 count_z=0;
			 }
		  }
		// cout<<vx[i]<<"  "<<vy[i]<<"  "<<vz[i]<<endl;
		 }
	 }
		 else
		 {

	  if(x[i]<980 && count_x==0)
		 {
			 
		 x[i]=x[i]+(vx[i]*(1/PHYSICS_UPDATE_RATE));
		 }
		 else
		 {
			count_x=1;
	    x[i]=x[i]-(vx[i]*(1/PHYSICS_UPDATE_RATE));
		 if(x[i]<30)
			 {
				 count_x=0;
			 }
		 }

		  if(y[i]<980 && count_y)
		  {
			   
		       y[i]=y[i]+vy[i]*(1/PHYSICS_UPDATE_RATE);
		  }
		  else
		  {    count_y=1;
			   y[i]=y[i]-vy[i]*(1/PHYSICS_UPDATE_RATE);
			   if(y[i]<30)
			 {
				 count_y=0;
			 }
		  }
		  
		  if(z[i]>-980 && count_z==0)
		  {
		 z[i]=z[i]+vz[i]*(1/PHYSICS_UPDATE_RATE);
		  }
		  else
		  {       
			  count_z=1;
			   z[i]=z[i]-vz[i]*(1/PHYSICS_UPDATE_RATE);
			   if(z[i]>-30)
			 {
				 count_z=0;
			 }
		  }
		// cout<<vx[i]<<"  "<<vy[i]<<"  "<<vz[i]<<endl;
		 }
	 
	 
	 
	 
	 
	 
	 }}


 //}
 


 /////////////////////////////////////////////////////////////////////////////////////////////////////
 void fish::update_fast_ai()
 {
	  //cout<<"update ai"<<endl;
	// float delta_velocity;
	 //cout<<"update ai"<<endl;
	// float delta_velocity;
	 Vector3 delta_velocity;
	 float Acceleration;
	 update_slow_AI();
	 for(int i=0; i<total_fish;i++)
	 {
		 Vector3 fi(x[i], y[i], z[i]);
		 Vector3 su(sub1.xPosition, sub1.yPosition, sub1.zPosition);


		 if(culling_distance==true)
		 {
		 if(su.getDistance(fi) < culling_distance)
		 {
		 Vector3 actual_velocity(vx[i],vy[i],vz[i]);
		 Vector3 desire_velocity(dx[i],dy[i],dz[i]);
		 
//cout<<vx[i]<<"  "<<vy[i]<<"  "<<vz[i]<<"  "<<dx[i]<<"  "<<dy[i]<<"  "<<dz[i]<<"  ";

		 delta_velocity=desire_velocity-actual_velocity;
		// cout<<delta_velocity.x<<"  "<<delta_velocity.y<<"  "<<delta_velocity.z<<endl;
		 Acceleration=FISH_ACCELERATION_MAX * (1/_FAST_AI_UPDATE_RATE);
		// cout<<Acceleration<<"  "<<delta_velocity.getNorm()<<endl;
		 if (delta_velocity.getNorm() > Acceleration)
		 {
			 
			 delta_velocity=delta_velocity.getNormalized();
			 vx[i]+=(delta_velocity.x*Acceleration);
			 vy[i]+=(delta_velocity.y*Acceleration);
			 vz[i]+=(delta_velocity.z*Acceleration);
			 //cout<<i<<endl;
		 }
		 
		 }}
		 else
		 {

	       Vector3 actual_velocity(vx[i],vy[i],vz[i]);
		 Vector3 desire_velocity(dx[i],dy[i],dz[i]);
		 
//cout<<vx[i]<<"  "<<vy[i]<<"  "<<vz[i]<<"  "<<dx[i]<<"  "<<dy[i]<<"  "<<dz[i]<<"  ";

		 delta_velocity=desire_velocity-actual_velocity;
		// cout<<delta_velocity.x<<"  "<<delta_velocity.y<<"  "<<delta_velocity.z<<endl;
		 Acceleration=FISH_ACCELERATION_MAX * (1/_FAST_AI_UPDATE_RATE);
		// cout<<Acceleration<<"  "<<delta_velocity.getNorm()<<endl;
		 if (delta_velocity.getNorm() > Acceleration)
		 {
			 
			 delta_velocity=delta_velocity.getNormalized();
			 vx[i]+=(delta_velocity.x*Acceleration);
			 vy[i]+=(delta_velocity.y*Acceleration);
			 vz[i]+=(delta_velocity.z*Acceleration);
			 //cout<<i<<endl;
		 }
	 
	 
		 }}

 }



 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 void fish::update_slow_AI()
 {
float ai;
	
	 ai=total_fish*slow_ai;
	 
	 static int count;
	int total_near_fish=0;

	 for(int i=1;i<ai;i++)
	 {
		 Vector3 current_fish(x[count],y[count],z[count]);
		 for(int j=0;j<total_fish;j++)
		 {
			 Vector3 compared_fish(x[j],y[j],z[j]);
				 if(current_fish.isDistanceLessThan(compared_fish,FLOCK_DISTANCE_MAX))
				 {
					 total_near_fish++;
				 }
		 }
		 if(total_near_fish<FLOCK_COUNT_MIN)
		 {
			 Vector3 desire;
             desire=desire.getRandomUnitVector();
			 dx[count]=desire.x * FISH_SPEED_MAX;
             dy[count]=desire.y * FISH_SPEED_MAX;
             dz[count]=desire.z * FISH_SPEED_MAX;
			//cout<<count<<"  " <<desire<<endl;
		 }
		 else
		 {
			 dx[count]=0;
             dy[count]=0;
             dz[count]=0;
		 }
	  count++;
	 // cout<<count<<endl;
	  if(count>=total_fish)
	  {
		  count=0;
	  }
	 }	
 }



 //////////////////////////////////////////////////////////////////////////////////////////////////////
 float fish::ai_increment()
 {
	 if(slow_ai<0.3)
	 {
	 slow_ai+=0.01;
	 }
	 return(slow_ai);

 }


 //////////////////////////////////////////////////////////////////////////////////////////////////////
 float fish::ai_decrement()
 {
	 if(slow_ai>0.005)
	 {
	 slow_ai-=0.005;
	 }

	 return(slow_ai);
 }



 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 void fish::fish_decrement()
 {
	 if(total_fish>0)
	 {
		 total_fish=total_fish-1;
	 }
 }


 /////////////////////////////////////////////////////////////////////////////////////////////////
 void fish::fish_increment()
 {
	  if(total_fish<2000)
	 {
		 total_fish=total_fish+1;
	 }
 }


 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 void fish:: floor_surface()
 {

	 glEnable(GL_DEPTH);

	 glColor3f(1.0, 1.0, 1.0);
		
	 int xs= 20;
	 int zs=20;
	//static int k=0;
	 static int rad=0;
	
	ofstream outFile;

	
	// k=1;
	 
	 
  glPushMatrix();

      // glColor3d(1.0, 1.0, 1.0);
     
	    
       glEnable(GL_TEXTURE_2D);

       TextureManager::activate("seafloor.bmp");

	  

	   /* for(int i=0; i<=54; i++)
	{

		 for(int j=0;j<=54;j++)
	{   

       glBegin(GL_QUADS);

	
			 glTexCoord2d(0,1);  
			 glVertex3d(fx[i][j],fy[i][j],-fz[i][j]);

			 glTexCoord2d(0,0);  
			 glVertex3d(fx[i][j+1],fy[i][j+1],-fz[i][j+1]);

			 glTexCoord2d(1,0);  
			 glVertex3d(fx[i+1][j+1],fy[i+1][j+1],-fz[i+1][j+1]);
			 
			 glTexCoord2d(1,1);  
			 glVertex3d(fx[i+1][j],fy[i+1][j],-fz[i+1][j]);



			
		
		 
		   
		 
		glEnd();
		 
		 }}*/



     //  glDisable(GL_TEXTURE_2D);

	    for (int k = 0; k <  54; k++)
        {
            glBegin(GL_TRIANGLE_STRIP);

                // iteration 0 handles first two points of first triangle;

                // every subsequent iteration finishes two triangles
                for(unsigned int i = 0; i <= 54; i++)
                {
                    // makes use of texture wrapping

                    glTexCoord2d(i, 1);   glVertex3d(i*20, fy[i][k], -k*20     );
                    glTexCoord2d(i, 0);   glVertex3d(i*20, fy[i][k+1], -(k + 1)*20);
                }
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

		 
		 

glPopMatrix();
		   
		 
	 

 }

 void fish::fish_surface_collision()
 {
	// cout<<sub_inside<<endl;
	 for(int i=0; i<total_fish; i++)
	 {
		 if(sub_inside==true)
		 {

		 
       if(y[i]+8>1000)
	   {
		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vy[i]=-vy[i];
	   }
		}

		 else
		 {
               if(y[i]+8>2000 )
	   {
		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vy[i]=-vy[i];
	   } 
			   if(y[i]-8<1000)
			   {
				   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vy[i]=-vy[i];
			   }

		 }


	   /*if(y[i]-8<0)
	   {
		   vy[i]=-vy[i];
		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
	   }
*/
	   if(x[i]-8<0)
       {
		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vx[i]=-vx[i];
	   }

	   if(x[i]+8>1000)
       {
		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vx[i]=-vx[i];
	   }
	    if(z[i]-8<-1000)
		{

		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vz[i]=-vz[i];
		}
		 if(z[i]+8>0)
		{

		   x[i]=px[i];
		   y[i]=py[i];
		   z[i]=pz[i];
		   vz[i]=-vz[i];
		}


	 }
 }




	
	

	
 void fish::catching_sound()
 {
	 static int shouldPlaySound=1;
	 alSourceStop(source[0]);

	 if(shouldPlaySound){
    loadSound();
    playSound(1);
    shouldPlaySound = 0;
  }else{
    ALint state;
    alGetSourcei(source[1], AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING){
	  shouldPlaySound1=1;
      cleanUpSound();
    }
  }
	
	

	glFlush();
}
 
 void fish::background_sound()
 {
	// cout<<"hii";
	 
	 //alSourceStop(source[0]);

	 if(shouldPlaySound1){
    loadSound();
    playSound(0);
	cout<<"hii";
    shouldPlaySound1 = 0;
  }else{
    ALint state;
    alGetSourcei(source[0], AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING){
      cleanUpSound();
	  shouldPlaySound1=1;
    }
	//glFlush();
  }
	
	

	glFlush();
}

 ///////////////////////////////////////////////////////////////////////////////////////////////////////

  void fish:: fish_floor_collision()
   { 
	   //cout<<"O";
	   for(int m=0;m<total_fish;m++)
	   {


	   q_k= ((-1.0*z[m])/c_z);
	   q_i = (x[m]/c_x);

	  
	   float f_k= q_k-floor(q_k);
	   float f_i= q_i-floor(q_i);
	   Vector3 N;

	   
	  //  cout<<f_k<<"  "<<f_i<<"  ";
	   
	    
	   int k=floor(q_k);
	   int i=floor(q_i);
	   Vector3 P01;

	   if(f_k + f_i < 1)
	   {
		   
	   Vector3 P0( (i*c_x), fy[i][k],  k*c_z);
	   Vector3 P1( i*c_x, fy[i+1][k],  (k+1)*c_z);
	   Vector3 P2((i+1)*c_x, fy[i][k+1], k*c_z);
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
		   
	   Vector3 P0( (i+1)*c_x, fy[i+1][k+1], (k+1)*c_z);  
	   Vector3 P1( i*c_x, fy[i+1][k], (k+1)*c_z);  
	   Vector3 P2((i+1)*c_x, fy[i][k+1], k*c_z);  
	   Vector3 P3=(P2-P0);   
	   Vector3 P4=(P1-P0);  
	   N=P3.crossProduct(P4);  
	   P01=P0;    

	  

	   }

	   

	   double dot_pro = N.dotProduct(P01);
	   double yax= (((-N.x * x[m])-(N.z*(-z[m]))+dot_pro)/N.y);
	//  cout<<yax<<"  ";

	   if((y[m]-12) < yax)
	   {

		//   cout<<vxs<<"  "<<vys<<"  "<<vzs;
		   Vector3 Velocity(vx[i],vy[i],vz[i]);

		   /* if((y[m]-3) < yax)
			{
				y[m]=y[m]+3;
				
			}*/
		    Velocity=Velocity - (2.01 * (Velocity.projection(N)));
		    vx[m]=Velocity.x;
	        vy[m]=Velocity.y;
	        vz[m]=-Velocity.z;

			if((y[m]-5) < yax)
			{
				vy[m]+=5;
			}
	   }

	   
	   }

   }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  void fish:: fish_neighbour()
  {
	  
	//LinkedList link_neigh[500];
	  float total_distance=0;
	  
	  for(int i=0; i<total_fish; i++)
	  {   Vector3 disA(x[i], y[i], z[i]);
		  for(int j=0; j<total_fish; j++)
		  {
			  Vector3 disB(x[j],y[j],z[j]);

			  total_distance=disA.getDistance(disB);
			//  cout<<"total_distance"<<total_distance<<endl;
			if(total_distance<(FISH_NEIGHBOR_MAX_DISTANCE))
			  {
				 link_neigh[i].insertItem(j,total_distance);
			  }

		  }
		  
	  }
	  // link_neigh[1].printList();
	 // link_neigh[1].~LinkedList();
  }

  Vector3 fish:: seperation(int fish_no)
  {
	  Vector3 sep;
	  Vector3 curr_fish(x[fish_no],y[fish_no],z[fish_no]);
	  
	  
		  ListElement* curr1;
		  Vector3 arr[5];
		  curr1=link_neigh[fish_no].head;
		  if(curr1!=NULL)
		  {
		  curr1=curr1->next;
		  }
		  int ta=0;
		  int count=0;
		  Vector3 seperat_total(0,0,0);
		  while(curr1!=NULL)
		  {    
			 // cout<<"fish_no"<<curr1->fish_no<<endl;
			  if(curr1->distan<=15)
			  {
			  Vector3 next1(x[curr1->fish_no],y[curr1->fish_no],z[curr1->fish_no]);
			  float sep_dist1=pow(((FISH_SEPARATION_MAX_DISTANCE-(curr1->distan))/FISH_SEPARATION_MAX_DISTANCE),2);
			//  cout<<"sjjgj"<<curr1->fish_no<<endl;
			  Vector3 sub;
			  sub.x= next1.x-curr_fish.x;
			  sub.y= next1.y-curr_fish.y;
			  sub.z= next1.z-curr_fish.z;
			  arr[count].x= sub.x/curr1->distan;
			  arr[count].y= sub.y/curr1->distan;
			  arr[count].z= sub.z/curr1->distan;

			  arr[count].x = arr[count].x * sep_dist1;
			  arr[count].y = arr[count].y * sep_dist1;
			  arr[count].z = arr[count].z * sep_dist1;

			  count++;
			  }
			  curr1=curr1->next;
		  }

		  for(int i=0; i<count;i++)
		  {
			  
			    seperat_total.x=seperat_total.x+ arr[i].x;
			  
				seperat_total.y=seperat_total.y+ arr[i].y;
			    seperat_total.z=seperat_total.z+ arr[i].z;
		  }
		  
		  seperat_total.x=seperat_total.x * (FISH_SEPARATION_WEIGHT);
		  seperat_total.y=seperat_total.y * (FISH_SEPARATION_WEIGHT);
		  seperat_total.z=seperat_total.z * (FISH_SEPARATION_WEIGHT);
	//	 cout<<"seperat  "<<seperat_total<<endl;
		  
		  return(seperat_total);
      }

  Vector3 fish:: cohesion(int fish_no)
  {
	  Vector3 sep;
	  Vector3 curr_fish(x[fish_no],y[fish_no],z[fish_no]);
	  
	  
		  ListElement* curr1;
		  Vector3 arr[5];
		  curr1=link_neigh[fish_no].head;
		  if(curr1!=NULL)
		  {
		  curr1=curr1->next;
		  }
		  int ta=0;
		  int count=0;
		  Vector3 seperat_total(0,0,0);
		  while(curr1!=NULL)
		  {   
			 // cout<<"fish_no"<<curr1->fish_no<<endl;
			  Vector3 next1(x[curr1->fish_no],y[curr1->fish_no],z[curr1->fish_no]);
			  float sep_dist1=((FISH_NEIGHBOR_MAX_DISTANCE-(curr1->distan))/FISH_NEIGHBOR_MAX_DISTANCE);
			//  cout<<"sepdistance"<<sep_dist1<<endl;
			  Vector3 sub;
			  sub.x= curr_fish.x-next1.x;
			  sub.y= curr_fish.y-next1.y;
			  sub.z= curr_fish.z-next1.z;
			  arr[count].x= sub.x/curr1->distan;
			  arr[count].y= sub.y/curr1->distan;
			  arr[count].z= sub.z/curr1->distan;

			  arr[count].x = arr[count].x * sep_dist1;
			  arr[count].y = arr[count].y * sep_dist1;
			  arr[count].z = arr[count].z * sep_dist1;

			  count++;
		     
			  curr1=curr1->next;
		  }

		  for(int i=0; i<count;i++)
		  {
			  
			  seperat_total.x=seperat_total.x+ arr[i].x;
			  seperat_total.y=seperat_total.y+ arr[i].y;
			  seperat_total.z=seperat_total.z+ arr[i].z;
		  }
            
		  seperat_total.x=seperat_total.x * (FISH_COHESION_WEIGHT);
		  seperat_total.y=seperat_total.y * (FISH_COHESION_WEIGHT);
		  seperat_total.z=seperat_total.z * (FISH_COHESION_WEIGHT);
		 // cout<<"cohesion  "<<seperat_total<<endl;
		   return(seperat_total);
      }


  Vector3 fish:: alignment(int fish_no)
  {
	  Vector3 sep;
	  Vector3 curr_fish(x[fish_no],y[fish_no],z[fish_no]);
	  
	  
		  ListElement* curr1;
		  Vector3 arr[5];
		  curr1=link_neigh[fish_no].head;
		  if(curr1!=NULL)
		  {
		  curr1=curr1->next;
		  }
		  int ta=0;
		  int count=0;
		  Vector3 seperat_total(0,0,0);
		  while(curr1!=NULL)
		  {   
			// cout<<"fish_no"<<curr1->fish_no<<endl;
			  Vector3 next1(x[curr1->fish_no],y[curr1->fish_no],z[curr1->fish_no]);
			  float sep_dist1=((FISH_NEIGHBOR_MAX_DISTANCE-(curr1->distan))/FISH_NEIGHBOR_MAX_DISTANCE);
			// cout<<"sepdistance"<<sep_dist1<<endl;
			  arr[count].x=sep_dist1*vx[curr1->fish_no];
			  arr[count].y=sep_dist1*vy[curr1->fish_no];
			  arr[count].z=sep_dist1*vz[curr1->fish_no];
			  count++;
		     
			  curr1=curr1->next;
		  }

		  for(int i=0; i<count;i++)
		  {
			  
			  seperat_total.x=seperat_total.x+ arr[i].x;
			  seperat_total.y=seperat_total.y+ arr[i].y;
			  seperat_total.z=seperat_total.z+ arr[i].z;
		  }

		  seperat_total.x=seperat_total.x * (FISH_ALIGNMENT_WEIGHT);
		  seperat_total.y=seperat_total.y * (FISH_ALIGNMENT_WEIGHT);
		  seperat_total.z=seperat_total.z * (FISH_ALIGNMENT_WEIGHT);

		  // cout<<"alignment_total  "<<seperat_total<<endl;
		   return(seperat_total);
      }


 int fish::total_fish_return()
 {
	 return(total_fish);
 }

 int fish::fish_shark_collision(float p, float q, float r)
 {
	 for(int i=0;i<total_fish;i++)
	 {
		 Vector3 fish_position(x[i],y[i],z[i]);
		 Vector3 shark_position(p,q,r);
		 if(fish_position.getDistance(shark_position)<30)
		 {
			 
			 invisible_fish(i);
			 return(0);
		 }
	 }
	 return(1);
 }


  void fish::playSound(int i){
 // alSourcei (source[0], AL_LOOPING,  AL_TRUE );
  //alSourcei (source[0], AL_LOOPING,  AL_TRUE );
  alSourcePlay(source[i]);
}

 void fish::loadSound(){
  // Load pcm data into buffer
	 alGenBuffers(5, buffers);
	// alBufferData(buffers[0],format,data,size,freq);
     alutLoadWAVFile("FreedomDance.wav", &format, &data, &size, &freq, &loop);
	 alBufferData(buffers[0],format,data,size,freq);
  // Create sound source (use buffer to fill source)
	 alutUnloadWAV(format,data,size,freq);
  alGenSources(5, source);
  alSourcei(source[0], AL_BUFFER, buffers[0]);
  alutLoadWAVFile("catching.wav", &format, &data, &size, &freq, &loop);
	 alBufferData(buffers[1],format,data,size,freq);
	 alutUnloadWAV(format,data,size,freq);
	 alSourcei(source[1], AL_BUFFER, buffers[1]);
}
void fish::cleanUpSound(){
  // Clean up sources and buffers
  alDeleteSources(1, source);
  alDeleteBuffers(1, buffers);
}