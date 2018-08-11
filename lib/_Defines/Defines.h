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
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2000

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2 - 250, false)

#define GOALIE_POS (DEFEND_GOAL + Vector(50, 50, false))


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
#define ANGLE_TIGHTENER_LEFT 0.4 //Small orbit left scalar (multiply the current ball angle then move)
#define ANGLE_TIGHTENER_RIGHT 0.5 //Small orbit right scalar (multiply the current ball angle then move)
#define SMALL_OFFSET_LEFT 25 //Small orbit left offset
#define SMALL_OFFSET_RIGHT 45 //Small orbit right offset

#define ORBIT_DISTANCE 240 //Radius of circle for tangent orbit
#define SMALL_ORBIT 15 //Angle small orbit is called
#define BRAKE_ANGLE_LEFT 8 //The angle which the robot brakes on the left
#define BRAKE_ANGLE_RIGHT 40 //The angle which the robot brakes on the right
#define BRAKE_DISTANCE 450
#define SMALL_ORBIT_LEFT 10 //To increase small orbit range on the left
#define SMALL_ORBIT_RIGHT 15 //To increase small orbit range on the right
#define BIG_ORBIT_LEFT 0 //To increase big orbit range on the left
#define BIG_ORBIT_RIGHT 0 //To increase big orbit range on the right
#define SKEW_DISTANCE 500 //Distance where Big orbit skewing takes effect

#define BIG_ORBIT 50 //Angle Big Orbit is called
#define BIG_SKEWER 0.5 //Big Orbit Skew Factor
#define SLOW_DISTANCE 400 // Maximum distance to the ball where the robot is slowed
#define BIG_SLOWER 1 // Slower for certain parts of orbit

#define SLOW_ANGLE 150 //Angle where Orbit is slowed
#define SLOW_SPEED 0.6 //Factor orbit is slowed

#define TANGENT_SLOW_DOWN 100 //The angle where tangent orbit slows down
#define TANGENT_SLOW_DOWN_MAG 400

#define GOAL_TRACK_DIS 240 //Distance ball must be away from robot to goal track

#define CENTRE_TIME 1000
/* ----------------------------------------*/


#define DEFEND_SMALL_ANGLE 10

#define NORMAL_SPEED 200
#define MAX_SPEED 230
#define RETURN_SPEED 60


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
