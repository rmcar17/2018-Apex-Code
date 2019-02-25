#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

/* ---------------------General---------------------- */
#define ROBOT 1
#define ATTACK_BLUE false
#define NORMAL_SPEED 100
/* ---------------------Attack----------------------- */
#define SHOOTING_SPEED 140
#define GOAL_TRACK false
/* ---------------------Defend----------------------- */
#define GOALIE_SPEED 230
#define MAX_SPEED 230
/* -------------------------------------------------- */

// Compass
#define IMU_CALIBRATION_COUNT 500

#define SHOOTANGLE_KP 1.3
#define SHOOTANGLE_KI 0
#define SHOOTANGLE_KD 0.5

#define ROTATION_KP 1.2
#define ROTATION_KI 0
#define ROTATION_KD 0.14

#define ATTACK_KP 1.5
#define ATTACK_KI 0
#define ATTACK_KD 0.05

#define GOAL_KP 0.5 // 0.25
#define GOAL_KI 0
#define GOAL_KD 0.04 // 0.03

// Coordinates
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2000

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2 - 250, false)

#define GOALIE_POS (DEFEND_GOAL + Vector(0, 250, false))


// ORBIT
#define POS_HOR_KP 0.7
#define POS_HOR_KI 0
#define POS_HOR_KD 0

#define POS_VER_KP 0.7
#define POS_VER_KI 0
#define POS_VER_KD 0

#define GOAL_HOR_KP 7
#define GOAL_HOR_KI 0
#define GOAL_HOR_KD 0

#define GOAL_VER_KP 0.5
#define GOAL_VER_KI 0
#define GOAL_VER_KD 0

#define ROTATION_MULTIPLIER 20

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4.5


/*             ORBIT VALUES                */
/* ----------------------------------------*/
#define ANGLE_TIGHTENER_LEFT 0.6 //Small orbit left scalar (multiply the current ball angle then move)
#define ANGLE_TIGHTENER_RIGHT 0.7 //Small orbit right scalar (multiply the current ball angle then move)
#define SMALL_OFFSET_LEFT 25 //Small orbit left offset
#define SMALL_OFFSET_RIGHT 45 //Small orbit right offset

#if ROBOT == 2
  #define ORBIT_DISTANCE 230
#else
  #define ORBIT_DISTANCE 260 //Radius of circle for tangent orbit
#endif
#define SMALL_ORBIT 30 //Angle small orbit is called
#define SMALL_ORBIT_LEFT 0 //To increase small orbit range on the left
#define SMALL_ORBIT_RIGHT 0 //To increase small orbit range on the right
#define BIG_ORBIT_LEFT 0 //To increase big orbit range on the left
#define BIG_ORBIT_RIGHT 0 //To increase big orbit range on the right
#define SKEW_DISTANCE 500 //Distance where Big orbit skewing takes effect

#define BIG_ORBIT 50 //Angle Big Orbit is called
#define BIG_SKEWER 0.6 //Big Orbit Skew Factor
#define SLOW_DISTANCE 400 // Maximum distance to the ball where the robot is slowed
#define BIG_SLOWER 1 // Slower for certain parts of orbit

#define SLOW_ANGLE 150 //Angle where Orbit is slowed
#define SLOW_SPEED 0.7 //Factor orbit is slowed

#define TANGENT_SLOW_DOWN 100 //The angle where tangent orbit slows down
#define TANGENT_SLOW_DOWN_MAG 400

#define GOAL_TRACK_DIS 240 //Distance ball must be away from robot to goal track

#define CENTRE_TIME 1000
/*-----------------------------------------*/


/*            NEW ORBIT VALUES             */
/*-----------------------------------------*/
// Smaller angle = overshoot
// Larger angle = undershoot
#define SHOOTING_LEFT_ANGLE 60
#define SHOOTING_RIGHT_ANGLE 45

// Negative ratio = wider
// Positive ratio = tighter
#define SHOOTING_LEFT_RATIO 0.8

// Negative ratio = tighter
// Positive ratio = wider
#define SHOOTING_RIGHT_RATIO 0.3
/*-----------------------------------------*/

/*            DEFEND VALUES                */
#define DEFEND_POSITION Vector(-50, -350, false)

#define DEFEND_LEFT_I 100
#define DEFEND_RIGHT_I -180

#define SURGE_DISTANCE -500

#define ANG_GOALIE_KP 4.6
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
#if ROBOT == 1
	#define LIGHT_GATE_THRESH 500
#else
	#define LIGHT_GATE_THRESH 900
#endif

//KICKER
#define KICK_INTERVAL 1000
#define KICK_HIGH_TIME 65

// MOVEMENT
#define MOVEMENT_ANGLE_OFFSET 0
#define MOVEMENT_ROTATION_OFFSET 0
#define TOTAL_BRAKE_TIME 100

//BLUETOOTH

#define BT_START_1 250
#define BT_START_2 254
#define BT_DATA_SIZE 5

#define BT_SEND_TIME 40
#define BT_TIMEOUT 250

#endif
