#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

/* -------------------------------------------------- */
#define ROBOT 1

#define ATTACK_BLUE false
/* -------------------------------------------------- */

// Compass
#define IMU_CALIBRATION_COUNT 500

#define ROTATION_KP 5
#define ROTATION_KI 0
#define ROTATION_KD 0.2

#define GOAL_KP 1.5
#define GOAL_KI 0
#define GOAL_KD 0.05

// Coordinates
#define SUPERTEAM true

#if SUPERTEAM
  #define FIELD_WIDTH 4000
  #define  FIELD_LENGTH 6000

  #define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-600, false)
  #define DEFEND_GOAL Vector(FIELD_WIDTH / 2 - 100, 2000, false)

  #define CENTRE Vector(FIELD_WIDTH / 2 + 250, FIELD_LENGTH / 2, false)
#else
  #define FIELD_WIDTH 1820
  #define FIELD_LENGTH 2000

  #define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-300, false)
  #define DEFEND_GOAL Vector(FIELD_WIDTH / 2, 300, false)

  #define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2, false)
#endif


#define GOALIE_POS DEFEND_GOAL + Vector(0, 150, false)


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

#define GOAL_TRACK true

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4




/*             ORBIT VALUES                */
/* ----------------------------------------*/
#if ROBOT == 1
	#define ORBIT_FORWARD_ANGLE_TIGHTENER 0.9

	#define CLOSE_ORBIT_BACK Vector(390, 0)
	#define FAR_ORBIT_BACK Vector(480, 0)
	#define CLOSE_ORBIT_FRONT Vector(300, 0)
	#define FAR_ORBIT_FRONT Vector(350, 0)
	#define SIDE_DISTANCE Vector(390, 0)
	#define BACK_DISTANCE Vector(390,0)
	#define MAX_BACK_DISTANCE Vector(430,0)

	#define SMALL_ORBIT 18
	#define BIG_ORBIT 50
	#define SIDEWAYS_ORBIT 80
	#define BETWEEN_ORBIT 90
	#define BACK_ORBIT 105
#else
	#define ORBIT_FORWARD_ANGLE_TIGHTENER 0.9

	#define CLOSE_ORBIT_BACK Vector(390, 0)
	#define FAR_ORBIT_BACK Vector(480, 0)
	#define CLOSE_ORBIT_FRONT Vector(300, 0)
	#define FAR_ORBIT_FRONT Vector(350, 0)
	#define SIDE_DISTANCE Vector(370, 0)
	#define BACK_DISTANCE Vector(390,0)
	#define MAX_BACK_DISTANCE Vector(430,0)

	#define SMALL_ORBIT 20
	#define BIG_ORBIT 50
	#define SIDEWAYS_ORBIT 80
	#define BETWEEN_ORBIT 90
	#define BACK_ORBIT 105
#endif

/* ----------------------------------------*/


#define DEFEND_SMALL_ANGLE 10

#define NORMAL_SPEED 180
#define MAX_SPEED 220

// Camera
#define ATTACK_GOAL_OVERIDE true

#define CAM_BUFFER_NUM 6

#define CAM_CENTRE_X 120
#define CAM_CENTRE_Y 120

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
