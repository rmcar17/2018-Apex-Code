#ifndef DEFINES_H
#define DEFINES_H

#include <Vector.h>

// Compass
#define IMU_CALIBRATION_COUNT 100

#define ROTATION_KP 5
#define ROTATION_KI 0
#define ROTATION_KD 0.8

// MOTORS
#define MOTOR1_ANG 45
#define MOTOR2_ANG 135
#define MOTOR3_ANG 225
#define MOTOR4_ANG 315

// Coordinates
#define FIELD_WIDTH 1820
#define FIELD_LENGTH 2430

#define ATTACK_GOAL Vector(FIELD_WIDTH / 2, 300, false)
#define DEFEND_GOAL Vector(FIELD_WIDTH / 2, FIELD_LENGTH - 300, false)
// ORBIT

#define CENTRE_ATTACKER_DISTANCE 10
#define CENTRE_DEFENDER_DISTANCE 4

#define ORBIT_FORWARD_ANGLE_TIGHTENER 0.75

#define CLOSE_ORBIT Vector(160, 0)
#define FAR_ORBIT Vector(360, 0)

#define BIG_ORBIT 50
#define SMALL_ORBIT 20

#define DEFEND_SMALL_ANGLE 10

#define MAX_SPEED 255

// Camera
#define ATTACK_GOAL_OVERIDE false
#define OVERIDE_BLUE true

#define CAM_BUFFER_NUM 8

#define CAM_CENTRE_X 160
#define CAM_CENTRE_Y 120

#define CAM_SWITCH_D 16

#define CAMERA_HEIGHT 32
#define CAMERA_ORIGIN 96
#define CIRCLE_RADIUS 32
// LIGHT SENSORS

#define LS_NUM 4
#define LS_CALIBRATION_NUM 10

#define TSOP_NUM 12
#define TSOP_DELAY 2
#define TSOP_N 12
#define TSOP_S  3

#define READ_NUM 255
#define MIN_IGNORE_TSOP 10
#define MAX_IGNORE_TSOP 200

#define ANGLE_1 0
#define ANGLE_2 30
#define ANGLE_3 60
#define ANGLE_4 90
#define ANGLE_5 120
#define ANGLE_6 150
#define ANGLE_7 180
#define ANGLE_8 210
#define ANGLE_9 240
#define ANGLE_10 270
#define ANGLE_11 300
#define ANGLE_12 330

#endif
