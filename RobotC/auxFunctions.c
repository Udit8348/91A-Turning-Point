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
///
int commanded_arm_position; //global parameter for task

//this task uses arm motor and potentiometer on shaft
//to create a "servo" where global "commanded_arm_position"
//variable is the parameter to this task.  Motors will drive the
//arm/shaft so that the arm_potentiometer value equals the
//commanded_arm_control variable. Probably best to implement this
//using P or PI control

task arm_control()
{
 while(1) //infinite loop to drive arm to position & maintain it
 {
   if (commanded_arm_control > Sensor(arm_potentiometer) motor[arm]=127; //drive arm up
  else if (commanded_arm_control < Sensor(arm_potentiometer) motor[arm]=-127; //drive arm down
  else motor[arm]=0;  //Stop
  }
}

//this is the competition mode user_control task where the driver controls the
//drive train but just press certain predefined buttons on the controller to 
//autonomously move the arm to the desired positions

task user_control()
{
 int arm_position=400;               //This value a function on how you mount the potentiometer

 commanded_arm_position=400;  // 400 is potentiometer value when arm is down
                                            //900 is the upper limit of arm position
 startTask (arm_control);

 while(1)
 {

  ... code to set appropriate joystick values to drive motors
  ... code to controls claws

  //code to control arm position manually
  //if up or down button pressed, increment/decrement arm_position variable

  if (arm_up_button_pressed ) arm_position++; //Need to limit between 400 & 900
  if (arm_dn_button_pressed ) arm_position--;

  //code to make arm move to preset arm positions
  //Depending on which button pressed (Cortex Joystick controller)
  //Jam arm_position with appropriate Potentiometer values

  if (arm_preset_ground) arm_position=400; ground level ready to pickup
  if (arm_preset_low_goal_de) arm_position=500; just at low goal for de-scoring
  if (arm_preset_low_goal_sc) arm_position=600; just above low goal for scoring
  if (arm_preset_high_goa_del) arm_position=800; just at high goal for de-scoring
  if (arm_preset_high_goal_sc) arm_position=900;just above high goal for scoring

  //Send value to task arm_control() to move arm
  //independent of drive or claw functions

  commanded_arm_position = arm_position;
 }
}
///
#endif
