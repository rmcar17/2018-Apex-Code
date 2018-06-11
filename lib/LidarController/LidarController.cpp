#include <LidarController.h>

LidarController::LidarController(){

}

void LidarController::setup(){
  lidarFront.setup(LIDAR_FRONT_SERIAL);
  lidarRight.setup(LIDAR_RIGHT_SERIAL);
  lidarBack.setup(LIDAR_BACK_SERIAL);
  lidarLeft.setup(LIDAR_LEFT_SERIAL);
}

void LidarController::readAll(){
  lidarFront.read();
  lidarRight.read();
  lidarBack.read();
  lidarLeft.read();

  lidarVal[0] = lidarFront.getDistance();
  lidarVal[1] = lidarRight.getDistance();
  lidarVal[2] = lidarBack.getDistance();
  lidarVal[3] = lidarLeft.getDistance();
}

void LidarController::calculateCoords(){
  coords = Vector(FIELD_WIDTH-lidarVal[1]+lidarVal[3],FIELD_LENGTH-lidarVal[0]+lidarVal[2],false);
  coords = coords / 2;
}

Vector LidarController::getCoords(){
  return coords;
}
