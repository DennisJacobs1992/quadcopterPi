#include <iostream>
#include "LDR.h"
#include <wiringPiI2C.h>

using namespace std;

long curTime;
long prevTime;
bool ldrCheck;

LDR::LDR(){
    //tbd
}

void LDR::checkLDRstatus(){
    //tbd
} 

void LDR::getLDRValues(){
    //<future code to do it for all pins>
    prevTime = 
    for (digitalRead (3) != 1){
        //do noting (in future, an interupt based system should be used
    }
        while (ldrCheck == false)
        {
        
        }
    }
}