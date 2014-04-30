#ifndef __SUBMARINE1_H_INCLUDED__
#define __SUBMARINE1_H_INCLUDED__


#include "ObjLibrary/SpriteFont.h"
#include "GetGlut.h"
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/TextureManager.h"
#include <fstream>

const float SUBMARINE_MASS = 100.0 ; // kg

const float SUBMARINE_DRAG = 0.6 ;// fraction of speed left after 1 second

const float SUBMARINE_GRAVITY = -9.8;    // m*s^(-2)

const float SUBMARINE_BUOYANT_FORCE = 980.0 ;  // kg*m*s^(-2)

const float SUBMARINE_ENGINE_FORCE = 5000.0   ;// kg*m*s^(-2)

const float SUBMARINE_TURN_RATE = 120.0 ;  // degrees per second (or 2.0 radians/sec)

const float SUBMARINE_BUOYANCY_MIN = 0.1;

const float SUBMARINE_BUOYANCY_MAX = 1.5;

const float SUBMARINE_BUOYANCY_RATE = 0.25 ;  // s^(-1)

const float SUBMARINE_TILT_MIN = -5.0 ;  // degrees  (or -0.1 for radians)

const float SUBMARINE_TILT_MAX = 10.0 ;  // degrees (or 0.2 for radians)

 // m, total length = 10m, fish.obj is 1

const float SUBMARINE_SPHERE_RADIUS = 3.0 ; // m

const float SUBMARINE_SPHERE_MAX_DISTANCE = 9.0 ; // m

const float SUBMARINE_SPHERE_COUNT = 5;

const float SUBMARINE_OUTER_RADIUS =     SUBMARINE_SPHERE_MAX_DISTANCE + SUBMARINE_SPHERE_RADIUS ; // m

//const float FOG_DISTANCE = 250.0;

const float culling_distance=500.0;



class submarine1
{

public:

float vxs;
float vys;
float vzs;
float buoyancy;
float horizontal_angle;
bool update;
float angle_sub;
float physics_delta_time;
float AI_delta_time;
float ai_slow_value;
float delta_time;
float depth_color;
float yPosition  ;   //Initial Position is at the middle of the sea
float xPosition;      //Initial Position is at middle of the sea
float zPosition;
float red,green,blue;
float buoyancy_rate;
float tilt_rate;
float interpolation_value;
float increase_value;
float tilt_value;
float psx;
float psy;
float psz;
float c_z;
float c_x;
float q_k ;
float q_i ;
bool sphe;

submarine1();


void submarine(const ObjModel &submarine_obj);           //shape and Position of submarine
void depth_background();    //decide the background color according to the depth
//fish fis;                   //object of class fish
void submarine_update();
void submarine_physics_update();
void submarine_turn_rate();
void submarine_turn_clockwise();
void submarine_horizontal_velocity();
void buoyancy_increase();
void buoyancy_decrease();
void submarine_surface_collision();
void submarine_floor_collision();
void submarine_decreasing_velocity();
void skybox(submarine1 subs);
void skybox1();
	  
};
#endif 