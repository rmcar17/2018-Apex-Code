#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_MOTOR 0
#define DEBUG_COMPASS 0
#define DEBUG_PIXY 0
#define DEBUG_TSOPS 0
#define DEBUG_LIGHT 1

const bool DEBUG_ANY = DEBUG_MOTOR || DEBUG_COMPASS || DEBUG_PIXY || DEBUG_LIGHT;

#endif
