//
//  LightSensor.cpp
//  LightSensorSimulator
//
//  Created by Ashiro on 16/2/18.
//  Copyright © 2018 Ashiro. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "LightSensor.h"
using namespace std;

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
    for(int i = 0; i < sizeof(onWhite); i++){
        if(map[light[i][0]][light[i][1]]){
            onWhite[i] = true;
            any = true;
        }
        else{
            onWhite[i] = false;
        }
    }
}

void Robot::update(){
    if(any){
        if(danger==0){
            for(int i = 0; i < 12; i++){
                if(onWhite[i]){
                    initLight = i;
                    setDangers(initLight);
                    danger = 1;
                }
            }
        }
        if(danger!=0){
            maxDanger = 0;
            for(int i = 0; i < 12; i++){
                if(onWhite[i]){
                    if(maxDanger<dangers[i]){
                        maxDanger = dangers[i];
                    }
                }
            }
            danger = maxDanger;
            if(danger<=3){
                angle = initLight*30;
            }
            else if(danger>=4){
                angle = correctRange((initLight*30)+180, 360);
            }
        }
        
    }
    else{
        if(danger<=3){
            angle = -1;
            clearDangers();
            danger = 0;
        }
        else if(danger>=4){
            angle = correctRange((initLight*30)+180, 360);
        }
    }
}

void Robot::setDangers(int init){
    dangers[init] = 1;
    for(int i = 0; i < 5; i++){
        dangers[correctRange(init+i+1, 0, 11)] = i + 2;
        dangers[correctRange(init-i-1, 0, 11)] = i + 2;
    }
    dangers[correctRange(init+6, 0 , 11)] = 7;
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
    printf("Init: %d\nAngle: %d\nDanger: %d",initLight,angle,danger);
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
