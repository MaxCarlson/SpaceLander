/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: C-60
 *
 * Created on June 5, 2017, 9:49 PM
 */

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

/*
 * 
 */

class Lander{
public:
    //Landing variables set to moon defaults
    int time = 0, height = 200000, speed = 1600 , fuel = 7500;
    double gravity = 1.30;
    string location = "Moon";
    
    Lander(){
        cout << "Where would you like to attempt a landing? Enter one: Moon," << endl;
        cin >> location;
        
    }
    
    void setLocation(){
        if(location == "moon" || "Moon"){
            cout << "You are in a rocket approaching the Moon!" << endl;
            cout << "Th100e main computer failed, your pilot's unconscious!" << endl;
            cout << "You are to perform manual landing by controlling engines" << endl;
            cout << "specify fuel burning rate (kgs per second) for each 10 sec " << endl;
            cout << "and try to touch down with safe speed. Good luck!!!" << endl;
            cout << "Rocket weight: " << fuel << " kg" << endl;
        }
    }
    
    void printGame(){
        cout << "Time" << "   Height(m)" << "   Speed(m/s)" << "   Fuel(kg)" << "   Gravity(m/s^2)" << endl;
        
    }
};

int main(int argc, char** argv) {

    Lander newLanding;
    newLanding.setLocation();
    newLanding.printGame();
    
    return 0;
}

