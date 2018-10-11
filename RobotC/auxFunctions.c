/*
    This file is largely untested, and requires a port to PROS3, mostly for brainstorming
*/

#ifndef _AUX_FUNCTIONS
#define _AUX_FUNCTIONS

#DEFINE BATTERY_HIGH = 14.7
#DEFINE BATTERY_LOW = 13.2


//float: Return a more accurate estimation of the battery voltage
float smartBatteryPercentage()
{
    float percentage  = ((nImmediateBatteryLevel / 1000.0) - BATTERY_LOW) / (BATTERY_HIGH - BATTERY_LOW) * 100.0;
    /*
    Normally battery percentage would be calculated by dividing the current value by the max value and converting the value
    to a percentage. This approch does not accurately represent the percentage of power left in the batteries because 
    batteries are considered to be low even if their voltage is not 0. In fact it is bad for batteries to be completely
    discharged. Take for example a 7.2V battery would be considered low at 6.9V, when the robot no longer functions at full
    power. Taking a standard percentage, 6.9 is 95%, when it should really be 0%. This would be correct if the battery could
    be drained down to 0V, like mentioned before, this is harmful for the battery becuase it can enter a definitely dead
    state. The correct method to estimate the battery voltage is to assume that 6.9V is the theoretical 0V.So, the dead
    battery voltage must be subtracted from both the current voltage and highest possible voltage of the battery. This creates
    an ofset range which can be used to accurately estimate the voltage of the battery.
    
    Say the battery is at 6.9V. Using the the smart method: (6.9-6.9)/(7.2-6.9) * 100 = 0%. This is obviously just a 
    calculation, and the battery is not actually at 0%, however based on the performace that we are expecting from the robot
    the battery would be considered dead, so 0% @6.9V accurately represents that.
    */
    return percentage;
}

//int: takes raw input and returns slewed mtr values
int slewRate()
{
    if(abs(abs(motorPower) - abs(lastPower)) > slewRate){
        motorPower = lastPower + sgn(motorPower) * slewRate;
        /*
            If the new value is higher than the accepted change in speed, then it gets limited by the max rate of change. The
            rate of change is determined by the wait time of the loop.
        */
    }    
   lastPower = motorPower;
   return motor power;  
}

#endif
