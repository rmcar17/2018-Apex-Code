#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

// Compass
#define IMU_CALIBRATION_COUNT 500

#define ROTATION_KP 13
#define ROTATION_KI 0
#define ROTATION_KD 0.3

#define GOAL_KP 0.9
#define GOAL_KI 0
#define GOAL_KD 3

// Coordinates
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2430

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, 300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH - 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2, false)

// ORBIT
#define GOAL_TRACK true

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4

#define ORBIT_FORWARD_ANGLE_TIGHTENER 2

#define CLOSE_ORBIT Vector(400, 0)
#define FAR_ORBIT Vector(550, 0)

#define BIG_ORBIT 25
#define SMALL_ORBIT 15

#define DEFEND_SMALL_ANGLE 10

#define MAX_SPEED 200

// Camera
#define ATTACK_GOAL_OVERIDE true
#define OVERIDE_BLUE false

#define CAM_BUFFER_NUM 6

#define CAM_CENTRE_X 105
#define CAM_CENTRE_Y 105

#define CAM_SWITCH_D 16

#define CAMERA_HEIGHT 135
#define CAMERA_ORIGIN 207
#define CIRCLE_RADIUS 32
#define PIXEL_TO_MM 50 / 227
// LIGHT SENSORS

#define LS_NUM 4
#define LS_CALIBRATION_NUM 10

#endif
