// Name Radhey Shah, Id:200333585, 
//Assignment-1, CS-409


#ifndef __FISH_H_INCLUDED__
#define __FISH_H_INCLUDED__


#include "ObjLibrary/SpriteFont.h"
#include "GetGlut.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/TextureManager.h"
#include <fstream>
#include"LinkedList.h"
#include "submarine1.h"
#include "alut.h"
const int FISH_SPEED_MAX = 10 ; // m/s
const float PHYSICS_UPDATE_RATE = 100.0 ; // per second

const float _FAST_AI_UPDATE_RATE =  40.0;  // per second

 const float SLOW_AI_UPDATE_FRACTION = 0.01;  // per fast AI update

const float FISH_MASS = 1.0;  // kg

//const float FISH_SPEED_MAX = 20.0;  // m/s

const float FISH_ACCELERATION_MAX = 10.0;  // m/s^2

const float FLOCK_DISTANCE_MAX = 100.0 ; // m

const float FLOCK_COUNT_MIN = 5;
const float FISH_RADIUS = 5.0;  

const int FISH_NEIGHBOR_MAX_COUNT = 4;

const float FISH_NEIGHBOR_MAX_DISTANCE = 150.0;

const float FISH_SEPARATION_MAX_DISTANCE = 15.0;
//const float SUBMARINE_SPHERE_MAX_DISTANCE = 9.0 ; //
const float FISH_SEPARATION_WEIGHT = 0.5;

const float FISH_COHESION_WEIGHT   = 0.2;

const float FISH_ALIGNMENT_WEIGHT  = 0.3;




//const float SUBMARINE_MASS = 100.0 ; // kg

class fish
{
private:
	
	
	double px[2000]; // X position of fish
	double py[2000]; 
	double pz[2000];
	float red[2000]; // red,green,blue value of a fish
	float green[2000];
	float blue[2000];
	bool invisible_fish(int i);
	int score;
	int diamond[2000];
	bool is_there;
	int counter;
	
	double dx[2000];
	double dy[2000];
	double dz[2000];
	double slow_ai;
	double fx[100][100];
	double neigh[1000][FISH_NEIGHBOR_MAX_COUNT];
	
	double fz[200][100];
	double fu[200][100];
	double fv[200][100];
	double theta;
	double pi;
	double r;
public:
	double x[2000]; // X position of fish
	double y[2000]; 
	double z[2000];
	double vx[2000];
	double vy[2000];
	double vz[2000];
	float c_z;
    float c_x;
    float q_k ;
    float q_i ;
	double fy[200][100];
	bool is_culling;
	void fish_position_color(ObjModel spiky_obj);
	fish();     // contructor
	int no_fish(); // return total number of fish
	void collision_detection(float xPosition,int yPosition,int zPosition);//detect the collision between fish and submarine
	bool is_finish(); //whether game is finished or not
	int my_score(); // my current score
	int is_diamond();
	void fish_speed();
	void update_physics(submarine1 subs);
	void update_fast_ai();
	void update_slow_AI();
	float ai_increment();
	float ai_decrement();
	void  fish_increment();
	void fish_decrement();
	void floor_surface();
	void fish_surface_collision();
	void catching_sound();
	bool sphere;
	void fish_floor_collision();
	void fish_neighbour();
	LinkedList link_neigh[500];
	Vector3 seperation(int fish_no);
	Vector3 cohesion(int fish_no);
	Vector3 alignment(int fish_no);
	int total_fish_return();
	int fish_shark_collision(float p, float q, float r);
    bool sub_inside;
	

void playSound(int i);
void loadSound();
void cleanUpSound();
void background_sound();


};

#endif 

