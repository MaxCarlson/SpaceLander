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
#include <math.h>       /* pow */
#include <string>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

/*
 * 
 */
bool run1 = true;

class Lander{
public:
    //Planet variables set to moon defaults
    long  height = 200000, radius = 1737100;
    float gravity = 1.304, g0gravity = 1.622;
    string location = "Moon";
    //Rocket variables
    int throttle = 0, rMass = 2134;
    float deltaV = 0, deltaMass = 0, Vexhaust = 2800, fuel = 8200, velocity = 1600;
    //Time increments
    double dt = 0.1, time = 0;
    int dtcounter = -1;
    //Orbital body crater stuff
    double rocketDiameter = 2.34, rocketDensity = 1.54, surfaceDensity = 2.5100, collapseFactor = 1.4;
    
    
    Lander(){
    }
    
    void setLocation(){
        cout << "Where would you like to attempt a landing? Enter one: Moon," << endl;
        cin >> location;
        if(location == "moon" || "Moon"){
            cout << "You are in a rocket approaching the Moon!" << endl;
            cout << "The main computer failed, your pilot's unconscious!" << endl;
            cout << "You are to perform manual landing by controlling engines" << endl;
            cout << "specify fuel burning rate (kgs per second) for each 10 sec " << endl;
            cout << "and try to touch down with safe speed. Good luck!!!" << endl;
            cout << "Rocket total weight: " << rMass+fuel << " kg" << endl;
        }
    }
    
    void printGame(){
        stringstream timetmp, heighttmp, speedtmp, fueltmp;
        timetmp << time; heighttmp << height; speedtmp << velocity; fueltmp << fuel;
        cout << "Time" << "   Height(m)" << "   Speed(m/s)" << "   Fuel(kg)" << "   Gravity(m/s^2)" << endl;
        cout << setw(4-timetmp.gcount())<< setprecision(0) << time; 
        cout << setw(11-heighttmp.gcount())<< height; 
        cout << setw(11-speedtmp.gcount())<< fixed << setprecision(0) << velocity;
        cout << setw(11-fueltmp.gcount()) << fuel;
        cout << setw(14) << setprecision(3) << gravity << endl;
        cout << "Burning rate: "; 
        cin >> throttle;
        
    }
    
    int numericIntegration(){
        for(double i = 0; i < dt*dtcounter-dt; i += dt){
            //Lander height, velocity, and mass changes
            height = height - velocity*dt;
            if (height <= 0) {
                height = 0;
                deltaV = 0;
                return 0;
            }
            if(fuel > 0){
                deltaMass = dt*throttle;
                deltaV = Vexhaust * deltaMass/(rMass+fuel);
                fuel -= deltaMass;
            } else {
                deltaV = 0;
            }
            //Gravity acceleration
            gravity = g0gravity * (radius*radius) / ((radius+height)*(radius+height));
            //Increase velocity according to gravity + decrease according to dV
            velocity += gravity*dt; 
            velocity -= deltaV;
            time += dt;
        }

    }
    
    void setdt(){
        //Number of steps per 10 second sim calc based on value of dt
        //Not working with anything other than dt 0.1!!
        for(double i = 0; i < 10; i+= dt){
            dtcounter ++;
        }
    }
    
    double craterCalculation(){
        //kinetic energy of rocket
        double KE = 0.5*(rMass+fuel)*(velocity*velocity);
        //kiloton conversion
        KE = KE * 0.000000000000239005736138;
        //impact crater size calculation km
        double craterDiameter = 0.07*collapseFactor * pow(KE*rocketDensity/surfaceDensity, 1/3.4);
        craterDiameter *= 1000;
        //cout << craterDiameter; 
        return craterDiameter;
    }
    
    void printLanding(){
        cout << endl;
        cout << "Touch down at " << setprecision(1) << time << " seconds" << endl;
        cout << "Landing speed was: " << setprecision(0) << velocity << " m/s" << endl;
        double crater = craterCalculation();
        if(velocity < 12){
            cout << "You've successfully landed! Not one person dead! One small step..." << endl; 
        } else if (velocity < 30){
            cout << "Any landing you can walk away from is a good one, ";
            cout << "unfortunately not everyone will be walking away from this one..." << endl;
            cout << "CRASH! Your landing created a new crater!" << endl;
            cout << setprecision(0) << crater << " meters wide!" << endl;
        } else {
            cout << "CRASH! Your landing created a new crater" << endl;
            cout << setprecision(0) << crater << " meters wide!" << endl;
        }
    }
    
    bool run(){        
        
        setLocation();
        setdt();
        while(run1 == true){
            printGame();
            int tmp = numericIntegration();
            if(height == 0){
                printLanding();
                cout << endl;
                cout << "Play again? Press 1 and ENTER";
                string enter;
                cin >> enter; 
                if(enter == "1"){
                    cout << endl;
                    run1 = false;
                } else{
                    return false;
                }
            }   
        }
    }
};



int main(int argc, char** argv) {

    Lander newLanding;
    
    newLanding.run();
    while(run1 == false){
        run1 = true;
        Lander newLanding;
        newLanding.run();
    }
    
    
    
        
    return 0;
}

