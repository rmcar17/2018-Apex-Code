#ifndef PINS_H
#define PINS_H

#include <Defines.h>
#include <Arduino.h>

// Light Sensor

const int lightPins[LS_NUM] = {33,34,35,36,37,38,39,21,22,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10};

// MOTORS

#define MOTORFR_PWM 4
#define MOTORFR_IN1 3
#define MOTORFR_IN2 2

#define MOTORBR_PWM 7
#define MOTORBR_IN1 6
#define MOTORBR_IN2 5

#define MOTORBL_PWM 10
#define MOTORBL_IN1 8
#define MOTORBL_IN2 9

#define MOTORFL_PWM 13
#define MOTORFL_IN1 12
#define MOTORFL_IN2 11

// TSOPS
#define TSOP_POWER 52
#define TSOP_1 50
#define TSOP_2 48
#define TSOP_3 46
#define TSOP_4 44
#define TSOP_5 42
#define TSOP_6 40
#define TSOP_7 38
#define TSOP_8 36
#define TSOP_9 34
#define TSOP_10 32
#define TSOP_11 30
#define TSOP_12 28

// Communication

#define MASTER_MOSI MOSI
#define MASTER_MISO MISO
#define MASTER_SCK ALT_SCK
#define MASTER_CS_TSOP CS0
#define MASTER_CS_LIGHT CS1
#define MASTER_CS_PIXY CS2

#define SLAVE_TSOP_MOSI MOSI
#define SLAVE_TSOP_MISO MISO
#define SLAVE_TSOP_SCK ALT_SCK
#define SLAVE_TSOP_CS CS0

#define SLAVE_LIGHT_MOSI MOSI
#define SLAVE_LIGHT_MISO MISO
#define SLAVE_LIGHT_SCK ALT_SCK
#define SLAVE_LIGHT_CS CS0

#endif
