#ifndef PINS_H
#define PINS_H

#include <Defines.h>
#include <Arduino.h>

// Light Sensor

const int lightPins[LS_NUM] = {A0, A1, A2, A3};

// MOTORS

#define MOTORFR_PWM 2
#define MOTORFR_DIR 56
#define MOTORFR_BRK 57
#define MOTORFR_REV false

#define MOTORBR_PWM 23
#define MOTORBR_DIR 52
#define MOTORBR_BRK 51
#define MOTORBR_REV false

#define MOTORBL_PWM 22
#define MOTORBL_DIR 21
#define MOTORBL_BRK 20
#define MOTORBL_REV false

#define MOTORFL_PWM 6
#define MOTORFL_DIR 49
#define MOTORFL_BRK 50
#define MOTORFL_REV true

#endif
