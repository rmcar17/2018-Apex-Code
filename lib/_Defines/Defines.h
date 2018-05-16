#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

// Compass
#define IMU_CALIBRATION_COUNT 100

#define ROTATION_KP 13
#define ROTATION_KI 0
#define ROTATION_KD 0.3

// Coordinates
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2430

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, 300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH - 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2, false)
// ORBIT

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4

#define ORBIT_FORWARD_ANGLE_TIGHTENER 0.75

#define CLOSE_ORBIT Vector(160, 0)
#define FAR_ORBIT Vector(360, 0)

#define BIG_ORBIT 50
#define SMALL_ORBIT 20

#define DEFEND_SMALL_ANGLE 10

#define MAX_SPEED 100

// Camera
#define ATTACK_GOAL_OVERIDE false
#define OVERIDE_BLUE true

#define CAMERA_UPDATE_TIME 47000

#define CAM_BUFFER_NUM 8

#define CAM_CENTRE_X 160
#define CAM_CENTRE_Y 120

#define CAM_SWITCH_D 16

#define CAMERA_HEIGHT 135
#define CAMERA_ORIGIN 207
#define CIRCLE_RADIUS 32
#define PIXEL_TO_MM 50 / 227
// LIGHT SENSORS

#define LS_NUM 4
#define LS_CALIBRATION_NUM 10

#endif
