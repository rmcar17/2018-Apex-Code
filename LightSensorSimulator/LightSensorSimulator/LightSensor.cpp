//
//  LightSensor.cpp
//  LightSensorSimulator
//
//  Created by Ashiro on 16/2/18.
//  Copyright © 2018 Ashiro. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <math.h>
#include "LightSensor.h"
using namespace std;

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603

void Robot::setCenter(int x, int y){
    center[0] = x;
    center[1] = y;
    light[0][0] = center[0] - 3;
    light[0][1] = center[1];
    light[1][0] = center[0] - 2;
    light[1][1] = center[1] + 1;
    light[2][0] = center[0] - 1;
    light[2][1] = center[1] + 2;
    light[3][0] = center[0];
    light[3][1] = center[1] + 3;
    light[4][0] = center[0] + 1;
    light[4][1] = center[1] + 2;
    light[5][0] = center[0] + 2;
    light[5][1] = center[1] + 1;
    light[6][0] = center[0] + 3;
    light[6][1] = center[1];
    light[7][0] = center[0] + 2;
    light[7][1] = center[1] - 1;
    light[8][0] = center[0] + 1;
    light[8][1] = center[1] - 2;
    light[9][0] = center[0];
    light[9][1] = center[1] - 3;
    light[10][0] = center[0] - 1;
    light[10][1] = center[1] - 2;
    light[11][0] = center[0] - 2;
    light[11][1] = center[1] - 1;
    updateOnWhite();
    for(int i = 0; i < 12; i++){
        printf("%d ",onWhite[i]);
    }
    printf("\n");
    update();
}

void Robot::updateOnWhite(){
    any = false;
    double vectorX = 0, vectorY = 0;
    for(int i = 0; i < sizeof(onWhite); i++){
        if(map[light[i][0]][light[i][1]]){
            onWhite[i] = true;
            any = true;
            vectorX += sin((450-i*30)*PI/180);
            vectorY += cos((450-i*30)*PI/180);
        }
        else{
            onWhite[i] = false;
        }
    }
    if(any){
        vectorAngle = correctRange((atan2(vectorY,vectorX)*180/PI),0,360);
    }
    else{
        vectorAngle = -1;
    }
}

void Robot::update(){
    if(any){
        if(danger == 0){
            // First time touching the line (when in bound)
            initAngle = vectorAngle;
            prevAngle = vectorAngle;
            lineAngle = vectorAngle;
            danger = 1;
        }
        if(danger >= 1 && danger <= 4){
            // Still in bound, reset initAngle
            if(inRange(vectorAngle,prevAngle,90)){
                initAngle = vectorAngle;
                lineAngle = vectorAngle;
            } else{
                danger = 5;
            }
        } else if(danger >= 5 && danger <= 7){
            // Half out the line
            if(inRange(vectorAngle,initAngle,90)){
                lineAngle = initAngle;
                danger = 1;
            }else{
                initAngle = correctRange(vectorAngle+180,0,360);
                lineAngle = initAngle;
            }
        }
    }
    else{
        if(danger<=4){
            // We're back in the bound
            initAngle = -1;
            vectorAngle = -1;
            lineAngle = -1;
            danger = 0;
        }
        else{
            // We're out
            lineAngle = initAngle;
            vectorAngle = -1;
        }
    }
    prevAngle = vectorAngle;
}

bool Robot::inRange(double value, double target, int range){
    double offset = value;
    value = 0;
    target = correctRange(target-offset, 0, 360);
    if(target <= range || target >= 360-range){
        return true;
    }
    else{
        return false;
    }

}

void Robot::setDangers(int init){
    dangers[init] = 1;
    for(int i = 0; i < 5; i++){
        dangers[correctAngleRange(init+i+1, 0, 11)] = i + 2;
        dangers[correctAngleRange(init-i-1, 0, 11)] = i + 2;
    }
    dangers[correctAngleRange(init+6, 0 , 11)] = 7;
    for(int i = 0; i < 12; i++){
        printf("%d ",dangers[i]);
    }
    printf("\n");
}

void Robot::clearDangers(){
    for(int i = 0; i < 12; i++){
        dangers[i] = 0;
    }
}

int Robot::correctRange(int value, int max){
    if(value > max){
        while(value > max){
            value -= max;
        }
    }
    return value;
}

int Robot::correctRange(int value, int min, int max){
    if(value > max){
        while(value > max){
            value -= max;
        }
    }
    if(value < min){
        while(value < min){
            value += max;
        }
    }
    return value;
}

int Robot::correctAngleRange(int value, int min, int max){
    if(value > max){
        while(value > max){
            value -= max+1;
        }
    }
    if(value < min){
        while(value < min){
            value += max+1;
        }
    }
    return value;
}


void Robot::pMap(){
    for(int i = 0; i < 30; i++){
        printf("\n");
    }
    for(int x = 0; x < 40; x++){
        for(int y = 0; y < 40; y++){
            tempMap[x][y] = map[x][y];
        }
    }
    for(int i = 0; i < 12; i++){
        tempMap[light[i][0]][light[i][1]] = 2;
    }
    tempMap[center[0]][center[1]] = 3;
    for(int x = 0; x < 40; x++){
        for(int y = 0; y < 40; y++){
            printf("%d ",tempMap[x][y]);
        }
        printf("\n");
    }
    printf("Init: %0.2lf\nlineAngle: %.02lf\nDanger: %d\nvectorAngle: %0.2lf",initAngle,lineAngle,danger,vectorAngle);
    printf("\n");
}

void Robot::up(){
    setCenter(center[0]-1, center[1]);
}

void Robot::down(){
    setCenter(center[0]+1, center[1]);
}

void Robot::left(){
    setCenter(center[0], center[1]-1);
}
void Robot::right(){
    setCenter(center[0], center[1]+1);
}
