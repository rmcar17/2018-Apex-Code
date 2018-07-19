#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

/* -------------------------------------------------- */
#define ROBOT 2

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
#define SUPERTEAM false

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

	#define FIELD_LEFT Vector(300,1140, false)
	#define FIELD_RIGHT Vector(1250, 1140, false)

	#define FIELD_BACK_LEFT Vector(440, 440, false)
	#define FIELD_BACK_RIGHT Vector(1300, 460, false)
	#define FIELD_FORWARD_LEFT Vector(360, 1770, false)
	#define FIELD_FORWARD_RIGHT Vector(1130, 1780, false)
	
	#define NEUTRAL_BACK_LEFT Vector(490, 800, false)
	#define NEUTRAL_BACK_RIGHT Vector(1200, 630, false)
	#define NEUTRAL_FORWARD_LEFT Vector(570, 1470, false)
	#define NEUTRAL_FORWARD_RIGHT Vector(1200, 1400, false)

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

#define GOAL_TRACK false

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4




/*             ORBIT VALUES                */
/* ----------------------------------------*/
#define ORBIT_DISTANCE 180
#define IN_DISTANCE 240
#define SMALL_ORBIT 10
#define BIG_ORBIT 70

/* ----------------------------------------*/


#define DEFEND_SMALL_ANGLE 10

#define NORMAL_SPEED 200
#define MAX_SPEED 255

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
