#include <LidarController.h>

LidarController::LidarController(){

}

void LidarController::setup(){
  lidarRight.setup(LIDAR_RIGHT_SERIAL);
  lidarBack.setup(LIDAR_BACK_SERIAL);
  lidarLeft.setup(LIDAR_LEFT_SERIAL);
}

void LidarController::update(){
  readAll();
  calculateCoords();
}

void LidarController::readAll(){
  lidarRight.read();
  lidarBack.read();
  lidarLeft.read();

  lidarVal[0] = lidarRight.getDistance();
  lidarVal[1] = lidarBack.getDistance();
  lidarVal[2] = lidarLeft.getDistance();
}

void LidarController::calculateCoords(){
  coords = Vector(FIELD_WIDTH-lidarVal[0]+lidarVal[2],lidarVal[1]*2,false);
  coords = coords / 2;
}

Vector LidarController::getCoords(){
  return coords;
}
