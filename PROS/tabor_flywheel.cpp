void flywheel(){
  if(controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_LEFT)){
    goalVel = 92;
  }
  if(controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_RIGHT)){
    goalVel = 83;
  }

  goalVel += controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_UP) - 
  controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_DOWN);
  if(controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_UP) &&
  controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_DOWN))
    goalVel = 0;
  motor_set_velocity(shooter1,-1*goalVel);
  motor_set_velocity(shooter2,goalVel);
  counts ++;
  if(!(counts%10)){
    float currentEnc = -1*motor_get_position(shooter1);
    Vel = (currentEnc-lastEnc)*(60.0/900.0);
    display_center_printf(2, "Velocity: %1.2f",Vel); 
    display_center_printf(3, "Position: %1.2f",(currentEnc)); 
    display_center_printf(4, "goal Vel: %d",goalVel); 
    display_center_printf(5, "Velocity Error: %f",fabs(Vel - goalVel) ); 


    lastEnc =currentEnc;
  }
  int intakeBut = controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_R2);
  int outtakeBut = controller_get_digital(CONTROLLER_MASTER,E_CONTROLLER_DIGITAL_R1);

  if(intakeBut && outtakeBut && abs(Vel - goalVel) < 1){
    motor_set_velocity(indexer,-50);
    motor_set_velocity(intake,-127);

  }else{
    motor_set_velocity(indexer,0);
    motor_set_velocity(intake,127*(outtakeBut - intakeBut));
  }
