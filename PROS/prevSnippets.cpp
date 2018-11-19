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
