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
#include <iomanip>
#include <sstream>

using namespace std;

/*
 * 
 */

class Lander{
public:
    //Planet variables set to moon defaults
    long time = 0, height = 200000, radius = 1737100;
    double gravity = 1.304, g0gravity = 1.622;
    string location = "Moon";
    //Rocket variables
    int fuel = 8200, throttle = 0, rMass = 2134, velocity = 1600;
    double deltaV = 0, deltaMass = 0, Vexhaust = 2800;
    //Time increments
    double dt = 0.1;
    
    Lander(){
        cout << "Where would you like to attempt a landing? Enter one: Moon," << endl;
        cin >> location;
        
    }
    
    void setLocation(){
        if(location == "moon" || "Moon"){
            cout << "You are in a rocket approaching the Moon!" << endl;
            cout << "The main computer failed, your pilot's unconscious!" << endl;
            cout << "You are to perform manual landing by controlling engines" << endl;
            cout << "specify fuel burning rate (kgs per second) for each 10 sec " << endl;
            cout << "and try to touch down with safe speed. Good luck!!!" << endl;
            cout << "Rocket weight: " << rMass+fuel << " kg" << endl;
        }
    }
    
    void printGame(){
        stringstream timetmp, heighttmp, speedtmp, fueltmp;
        timetmp << time; heighttmp << height; speedtmp << velocity; fueltmp << fuel;
        cout << "Time" << "   Height(m)" << "   Speed(m/s)" << "   Fuel(kg)" << "   Gravity(m/s^2)" << endl;
        cout << setw(4-timetmp.gcount()) << time; 
        cout << setw(11-heighttmp.gcount())<< height; 
        cout << setw(11-speedtmp.gcount()) << velocity;
        cout << setw(11-fueltmp.gcount()) << fuel;
        cout << setw(14) << setprecision(2) << gravity << endl;
        cout << "Burning rate: "; 
        cin >> throttle;
        
    }
    
    void numericIntegration(){
        //Lander height, velocity, and mass changes
        height = height - velocity*dt;
        deltaMass = dt*throttle;
        deltaV = Vexhaust * deltaMass/(rMass+fuel);
        fuel -= deltaMass;
        //Gravity acceleration
        gravity = g0gravity * (radius*radius) / ((radius+height)*(radius+height));
        
    }
    
    
};

int main(int argc, char** argv) {

    Lander newLanding;
    newLanding.setLocation();
    newLanding.printGame();
    
    return 0;
}

