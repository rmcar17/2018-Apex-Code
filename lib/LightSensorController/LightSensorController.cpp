#include "LightSensorController.h"

void LightSensorController::setup(){
	ls1.setup();
	ls2.setup();
	ls3.setup();
	ls4.setup();
	ls5.setup();
	ls6.setup();
	ls7.setup();
	ls8.setup();
	ls9.setup();
	ls10.setup();
	ls11.setup();
	ls12.setup();	
}

void LightSensorController::setThresh(int thresh1,int thresh2,int thresh3,int thresh4,int thresh5,int thresh6,int thresh7,int thresh8,int thresh9,int thresh10,int thresh11,int thresh12){
	ls1.setThresh(thresh1);
	ls2.setThresh(thresh2);
	ls3.setThresh(thresh3);
	ls4.setThresh(thresh4);
	ls5.setThresh(thresh5);
	ls6.setThresh(thresh6);
	ls7.setThresh(thresh7);
	ls8.setThresh(thresh8);
	ls9.setThresh(thresh9);
	ls10.setThresh(thresh10);
	ls11.setThresh(thresh11);
	ls12.setThresh(thresh12);
}

void LightSensorController::getVal(){
	lightValues[0] = ls1.GetVal();
	lightValues[1] = ls2.GetVal();
	lightValues[2] = ls3.GetVal();
	lightValues[3] = ls4.GetVal();
	lightValues[4] = ls5.GetVal();
	lightValues[5] = ls6.GetVal();
	lightValues[6] = ls7.GetVal();
	lightValues[7] = ls8.GetVal();
	lightValues[8] = ls9.GetVal();
	lightValues[9] = ls10.GetVal();
	lightValues[10] = ls11.GetVal();
	lightValues[11] = ls12.GetVal();
	onWhite[0] = ls1.onWhite();
	onWhite[1] = ls2.onWhite();
	onWhite[2] = ls3.onWhite();
	onWhite[3] = ls4.onWhite();
	onWhite[4] = ls5.onWhite();
	onWhite[5] = ls6.onWhite();
	onWhite[6] = ls7.onWhite();
	onWhite[7] = ls8.onWhite();
	onWhite[8] = ls9.onWhite();
	onWhite[9] = ls10.onWhite();
	onWhite[10] = ls11.onWhite();
	onWhite[11] = ls12.onWhite();
}