//
//  main.cpp
//  LightSensorSimulator
//
//  Created by Ashiro on 16/2/18.
//  Copyright © 2018 Ashiro. All rights reserved.
//

#include <iostream>
#include "LightSensor.h"
using namespace std;

Robot robot;

int main() {
    char input;
    robot.setCenter(20, 20);
    robot.pMap();
    cin >> input;
    while(input!='q'){
        switch (input) {
            case 'u':
                robot.up();
                break;
            case 'd':
                robot.down();
                break;
            case 'l':
                robot.left();
                break;
            case 'r':
                robot.right();
                break;
            default:
                break;
        }
        robot.pMap();
        cin >> input;
    }
    return 0;
}
