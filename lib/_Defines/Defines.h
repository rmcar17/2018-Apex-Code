#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

// Compass
#define IMU_CALIBRATION_COUNT 500

#define ROTATION_KP 5
#define ROTATION_KI 0
#define ROTATION_KD 0.2

#define GOAL_KP 1.5
#define GOAL_KI 0
#define GOAL_KD 0.05

// Coordinates
#define LIDAR_NUM 4

#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2430

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH-300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, 300, false)

#define GOALIE_POS DEFEND_GOAL + Vector(0, 300, false)

#define CENTRE Vector(FIELD_WIDTH / 2, FIELD_LENGTH / 2, false)

// ORBIT
#define POS_HOR_KP 0
#define POS_HOR_KI 0
#define POS_HOR_KD 0

#define POS_VER_KP 0
#define POS_VER_KI 0
#define POS_VER_KD 0

#define GOAL_HOR_KP 0
#define GOAL_HOR_KI 0
#define GOAL_HOR_KD 0

#define GOAL_VER_KP 0
#define GOAL_VER_KI 0
#define GOAL_VER_KD 0

#define GOAL_TRACK true

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4

#define ORBIT_FORWARD_ANGLE_TIGHTENER 0.25

#define CLOSE_ORBIT Vector(380, 0)
#define FAR_ORBIT Vector(450, 0)

#define SIDEWAYS_ORBIT 60
#define BIG_ORBIT 45
#define SMALL_ORBIT 10

#define DEFEND_SMALL_ANGLE 10

#define NORMAL_SPEED 150
#define MAX_SPEED 220

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

#define LS_NUM 24
#define LS_CALIBRATION_NUM 50

#endif
