#ifndef LIDAR_CONTROLLER_H
#define LIDAR_CONTROLLER_H

#include <Lidar.h>
#include <Common.h>
#include <Vector.h>
#include <Defines.h>
#include <Pins.h>

class LidarController {
  public:
    LidarController();

    void setup();
    void update();
    void readAll();
    void calculateCoords();
    Vector getCoords();
  // private:
    int lidarVal[LIDAR_NUM] = {0};
    Lidar lidarFront, lidarRight, lidarBack, lidarLeft;
    Vector coords = Vector(0,0);
};

#endif
