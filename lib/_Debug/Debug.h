#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_ORBIT 1
#define DEBUG_COMPASS 0
#define DEBUG_PIXY 0
#define DEBUG_TSOPS 0

const bool DEBUG_ANY = DEBUG_ORBIT || DEBUG_COMPASS || DEBUG_PIXY || DEBUG_TSOPS;

#endif
