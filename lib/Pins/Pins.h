#ifndef PINS_H
#define PINS_H

#include <Defines.h>
#include <Arduino.h>

// Light Sensor

const int lightPins[LS_NUM] = {A0, A1, A2, A3};

// MOTORS

#define MOTORFR_PWM 4
#define MOTORFR_DRV 3
#define MOTORFR_BRK 2

#define MOTORBR_PWM 7
#define MOTORBR_DRV 6
#define MOTORBR_BRK 5

#define MOTORBL_PWM 10
#define MOTORBL_DRV 8
#define MOTORBL_BRK 9

#define MOTORFL_PWM 13
#define MOTORFL_DRV 12
#define MOTORFL_BRK 11

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

#endif
