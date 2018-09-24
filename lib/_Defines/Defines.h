#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

/* -------------------------------------------------- */
#define ROBOT 2

#define ATTACK_BLUE true
/* -------------------------------------------------- */

// Compass
#define IMU_CALIBRATION_COUNT 500

#define SHOOTANGLE_KP 1.3
#define SHOOTANGLE_KI 0
#define SHOOTANGLE_KD 0.5

#define ROTATION_KP 4.5
#define ROTATION_KI 0
#define ROTATION_KD 0.1

#define ATTACK_KP 1.5
#define ATTACK_KI 0
#define ATTACK_KD 0.05

#define DEFEND_KP 0.7
#define DEFEND_KI 0
#define DEFEND_KD 0.035

// Coordinates
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2000

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2 - 250, false)

#define GOALIE_POS (DEFEND_GOAL + Vector(0, 60, false))


// ORBIT
#define POS_HOR_KP 0.7
#define POS_HOR_KI 0
#define POS_HOR_KD 0

#define POS_VER_KP 0.7
#define POS_VER_KI 0
#define POS_VER_KD 0

#define GOAL_TRACK true

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4




/*             ORBIT VALUES                */
/* ----------------------------------------*/
#define ANGLE_TIGHTENER_LEFT 0.9 //Small orbit left scalar (multiply the current ball angle then move)
#define ANGLE_TIGHTENER_RIGHT 1 //Small orbit right scalar (multiply the current ball angle then move)
#define SMALL_OFFSET_LEFT 25 //Small orbit left offset
#define SMALL_OFFSET_RIGHT 45 //Small orbit right offset


#if ROBOT == 2
  #define ORBIT_DISTANCE 260
#else
  #define ORBIT_DISTANCE 260 //Radius of circle for tangent orbit
#endif
#define SMALL_ORBIT 15 //Angle small orbit is called
#define BRAKE_ANGLE_LEFT 20 //The angle which the robot brakes on the left
#define BRAKE_ANGLE_RIGHT 25 //The angle which the robot brakes on the right
#define BRAKE_DISTANCE 500
#define SMALL_ORBIT_LEFT 0 //To increase small orbit range on the left
#define SMALL_ORBIT_RIGHT 0 //To increase small orbit range on the right
#define BIG_ORBIT_LEFT 0 //To increase big orbit range on the left
#define BIG_ORBIT_RIGHT 0 //To increase big orbit range on the right
#define SKEW_DISTANCE 500 //Distance where Big orbit skewing takes effect

#define BIG_ORBIT 50 //Angle Big Orbit is called
#define BIG_SKEWER 0.5 //Big Orbit Skew Factor
#define SLOW_DISTANCE 200 // Maximum distance to the ball where the robot is slowed
#define BIG_SLOWER 1 // Slower for certain parts of orbit

#define SLOW_ANGLE 150 //Angle where Orbit is slowed
#define SLOW_SPEED 0.6 //Factor orbit is slowed

#define TANGENT_SLOW_DOWN 100 //The angle where tangent orbit slows down
#define TANGENT_SLOW_DOWN_MAG 400

#define GOAL_TRACK_DIS 240 //Distance ball must be away from robot to goal track

#define CENTRE_TIME 1000
/*-----------------------------------------*/


/*            DEFEND VALUES                */
#define DEFEND_POSITION Vector(-50, -230, false)

#define DEFEND_LEFT_I 150
#define DEFEND_RIGHT_I -220

#define SURGE_DISTANCE -500

#define ANG_GOALIE_KP 2.5
#define ANG_GOALIE_KI 0
#define ANG_GOALIE_KD 0

#define H_GOALIE_KP 0.4
#define H_GOALIE_KI 0
#define H_GOALIE_KD 0

#define V_GOALIE_KP 0.15
#define V_GOALIE_KI 0
#define V_GOALIE_KD 0

#define SP_GOALIE_KP 1.2
#define SP_GOALIE_KI 0
#define SP_GOALIE_KD 0

/*=----------------------------------------*/

#define NORMAL_SPEED 180
#define MAX_SPEED 230
#define RETURN_SPEED 60


// Camera
#define ATTACK_GOAL_OVERIDE true

#define CAM_BUFFER_NUM 6

#define CAM_CENTRE_X 100
#define CAM_CENTRE_Y 115

#define CAM_SWITCH_D 16

#define CAMERA_HEIGHT 135
#define CAMERA_ORIGIN 207
#define CIRCLE_RADIUS 32
#define PIXEL_TO_MM 50 / 227
// LIGHT SENSORS

#define LS_NUM 24
#define LS_CALIBRATION_NUM 50

//LIGHT GATE
#define LIGHT_GATE_THRESH 660

//KICKER
#define KICK_INTERVAL 2000000
#define KICK_HIGH_TIME 5000

#endif
