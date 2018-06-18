#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
#include <Defines.h>

#define ROBOT 2

// Camera

#define cameraSerial Serial6

// Light Sensor

#define LIGHT_GATE_PIN 39

// Standard {33,34,35,36,37,38,39,21,22,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10}
// Robot 1 {33,34,35,36,22,37,39,21,38,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10};
#if ROBOT == 1
	const int brokenPins[] = {6,21};
	const int lightPins[LS_NUM] = {33,34,35,36,37,38,39,21,22,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10};
	const int lightThresh[LS_NUM] = {761,865,903,931,938,884,13,681,766,912,937,859,818,771,718,718,648,572,403,681,767,12,708,851};
#else
	const int brokenPins[] = {23};
	const int lightPins[LS_NUM] = {33,34,35,36,22,37,38,21,39,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10};
	const int lightThresh[LS_NUM] = {949,847,843,959,827,732,705,812,825,849,758,765,921,910,919,878,674,639,893,812,825,869,889,100};
#endif
// MOTORS
#define MOTORFR_PWM 2
#define MOTORFR_DIR 56
#define MOTORFR_BRK 57

#define MOTORBR_PWM 23
#define MOTORBR_DIR 52
#define MOTORBR_BRK 51

#define MOTORBL_PWM 22
#define MOTORBL_DIR 21
#define MOTORBL_BRK 20

#define MOTORFL_PWM 6
#define MOTORFL_DIR 49
#define MOTORFL_BRK 50

#if ROBOT == 1
	#define MOTORFR_REV true
	#define MOTORBR_REV true
	#define MOTORBL_REV true
	#define MOTORFL_REV true
#else
	#define MOTORFR_REV true
	#define MOTORBR_REV false
	#define MOTORBL_REV false
	#define MOTORFL_REV true
#endif

// KICKER
#define KICKER_PIN 53

// Teensy
#define TEENSY_LED 13

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
