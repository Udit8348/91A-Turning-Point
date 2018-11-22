//Arcade Drive (two joysticks)
int rLS = Controller1.get_analog(ANALOG_RIGHT_X) + Controller1.get_analog(ANALOG_LEFT_Y);	//raw joystick values
int rRS = Controller1.get_analog(ANALOG_RIGHT_X) - Controller1.get_analog(ANALOG_LEFT_Y);

//Arcade Drive (one joystick)
int rLS = Controller1.get_analog(ANALOG_LEFT_X) + Controller1.get_analog(ANALOG_LEFT_Y);	//raw joystick values
int rRS = Controller1.get_analog(ANALOG_LEFT_X) - Controller1.get_analog(ANALOG_LEFT_Y);

//Incremental Speed
int intakeSpeedDefault = 98;
int c,d =0;
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && c == 0){
	intakeSpeedDefault--;
  c=1;
}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
  c=0;
}

if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && d == 0){
	intakeSpeedDefault++;
	d=1;
}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
	d=0;
}

//Skills Presetting
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
	dscr.move_absolute(0, 100);
	while (!((dscr.get_position() > -5 && (dscr.get_position() < 5)))) {
		// Continue running this loop as long as the motor is not within +-5 units of its goal
		pros::delay(2);
	}
		dscr.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD);
}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
	dscr.move_absolute(-400, 125);
	while (!((dscr.get_position() > -405) && (dscr.get_position() < -395))) {
		// Continue running this loop as long as the motor is not within +-5 units of its goal
		pros::delay(2);
	}
		dscr.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD);
}

//old presetting system:
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			dscr.move_absolute(-1440, 100);
			while (!((dscr.get_position() > -1445 && (dscr.get_position() < -1435)))) {
    		// Continue running this loop as long as the motor is not within +-5 units of its goal
    		pros::delay(2);
  		}
				dscr.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD);
		}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			dscr.move_absolute(-1930, 100);
			while (!((dscr.get_position() > -1935) && (dscr.get_position() < -1925))) {
    		// Continue running this loop as long as the motor is not within +-5 units of its goal
    		pros::delay(2);
  		}
				dscr.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD);
		}


//Testing Flywheel Function, uses built in V5 velocity controller. Too agressive for flywheeel, no longer in use.
int targetRPM = 0;
int a = 0;
int b = 0;
//std::string zVel = "0";
//this function controls the flwheel
void flywheel() {
	/*
  if(vexRT[Btn8L] == 1) {targetPow = 64;	targetRPM = 136; I=0; segment=0; } // base
if(vexRT[Btn8U] == 1) {targetPow = 53;	targetRPM = 118; I=0; segment=0; } // mid-field
if(vexRT[Btn8R] == 1) {targetPow = 42;	targetRPM = 100; I=0; segment=0; } // at the bar
if(vexRT[Btn8D] == 1) {targetPow =  0;	targetRPM =   0; I=0; segment=0; }

if(vexRT[Btn6U]==1 && a==0) {targetRPM++; targetPow+=0.5; a=1;}	else if(vexRT[Btn6U]==0) a=0;
if(vexRT[Btn6D]==1 && b==0) {targetRPM--; targetPow-=0.5; b=1;}	else if(vexRT[Btn6D]==0) b=0;

  */
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_A)){targetRPM = 0;}
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_X)){targetRPM = -100;}
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){targetRPM = -150;}
if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_B)){targetRPM = -200;}

if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && a == 0){
  targetRPM+= -1;
  a=1;
}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
  a=0;
}

if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && b == 0){
  targetRPM++;
  b=1;
}else if(Controller1.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
  b=0;
}
//print velocity to the brain screen. This code did not work, .set_text does not allow text formatting. Fixed in newest version
//zVel = std::to_string(targetRPM);//@@ try this
//pros::lcd::set_text(0, "Flywheel Velocity");
//pros::lcd::set_text(1, zVel);
	
 //printing to controller only works with 100ms delay. this program printed to fast for controller to print correctly. Fixed in new version
 Controller1.print(0, 0, "RPM: %d", targetRPM);

//set velocity to the motor
fw.move_velocity(targetRPM);


}//end of function


