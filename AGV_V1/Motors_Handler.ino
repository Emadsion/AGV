#define CONVERT_STEPS_TO_ENC(x) (round((x) * ENCODERS_PPR / MOTORS_PPR))

inline void do_semi_step(u8 step_pin, u8 dir_pin, s8 dir)__attribute__((always_inline));
inline bool can_step(s32 target, s32 current)__attribute__((always_inline));


/****************************************************      Interface Function   ****************************************************************************************/
/*
  INPUTS : -Number of steps for each Wheel, datatype s32
          note that! -the number of steps can be positive or negative depends on the direction
                     -the number of steps can Only be integer
*/
//void run_motors_steps(s32 fr_steps, s32 fl_steps, s32 rr_steps, s32 rl_steps){
//  s8 fr_last_error = fr_target - enc_fr_position;
//  s8 fl_last_error = fl_target - enc_fl_position;
//  s8 rr_last_error = rr_target - enc_rr_position;
//  s8 rl_last_error = rl_target - enc_rl_position;
//
//  //Set New Targets to the motors
//  /* there will be an error because of the fraction return from the "CONVER_STEPTS_TO_ENC" must be put into account,
//  so we round the returned value*/
//  fr_target = enc_fr_position + CONVERT_STEPS_TO_ENC(fr_steps) + fr_last_error;
//  fl_target = enc_fl_position + CONVERT_STEPS_TO_ENC(fl_steps) + fl_last_error;
//  rr_target = enc_rr_position + CONVERT_STEPS_TO_ENC(rr_steps) + rr_last_error;
//  rl_target = enc_rl_position + CONVERT_STEPS_TO_ENC(rl_steps) + rl_last_error;
//  /* The motion will start moving right after setting the target */
//
//  if(fr_target > enc_fr_position) DEBUG_PRINTLN("DEBUG: fr_motor -> FORWARD");
//  else DEBUG_PRINTLN("DEBUG: fr_motor -> BACKWARD");
//
//  if(fl_target > enc_fl_position) DEBUG_PRINTLN("DEBUG: fl_motor -> FORWARD");
//  else DEBUG_PRINTLN("DEBUG: fl_motor -> BACKWARD");
//  
//  if(rr_target > enc_rr_position) DEBUG_PRINTLN("DEBUG: rr_motor -> FORWARD");
//  else DEBUG_PRINTLN("DEBUG: rr_motor -> BACKWARD");
//  
//  if(rl_target > enc_rl_position) DEBUG_PRINTLN("DEBUG: rl_motor -> FORWARD");
//  else DEBUG_PRINTLN("DEBUG: rl_motor -> BACKWARD");
//  
// 
//  /*Indicator to the User that the motion has been started*/
//  DEBUG_PRINTLN("DEBUG: start moving");
//
//  /*wait until the end of the motion*/
//  while((abs(fr_target - enc_fr_position) >= ENC_ERROR_MIN) || (abs(fl_target - enc_fl_position) >= ENC_ERROR_MIN) ||
//        (abs(rr_target - enc_rr_position) >= ENC_ERROR_MIN) || (abs(rl_target - enc_rl_position) >= ENC_ERROR_MIN)){
//    if(f){
//      DEBUG_PRINT("e_fr = "); DEBUG_PRINT((long)(fr_target - enc_fr_position));
//      DEBUG_PRINT("  e_fl = "); DEBUG_PRINT((long)(fl_target - enc_fl_position));
//      DEBUG_PRINT("  e_rr = "); DEBUG_PRINT((long)(rr_target - enc_rr_position));
//      DEBUG_PRINT("  e_rl = "); DEBUG_PRINTLN((long)(rl_target - enc_rl_position));
//      f = false;
//    }
//  }
//
//  /*Indicator to the User that the motion has been finished and ERROR Status for Each motor*/
//  DEBUG_PRINTLN("\nDEBUG: end moving\n");
//  DEBUG_PRINT("DEBIG: front-right motor error = ");
//  DEBUG_PRINTLN((long)(fr_target - enc_fr_position));
//  DEBUG_PRINT("DEBIG: front-left motor error  = ");
//  DEBUG_PRINTLN((long)(fl_target - enc_fl_position));
//  DEBUG_PRINT("DEBIG: rear-right motor error  = ");
//  DEBUG_PRINTLN((long)(rr_target - enc_rr_position));
//  DEBUG_PRINT("DEBIG: rear-left motor error   = ");
//  DEBUG_PRINTLN((long)(rl_target - enc_rl_position));
//  DEBUG_PRINTLN("\n");
//  
//}
//

void run_motors_steps(s32 fr_steps, s32 fl_steps, s32 rr_steps, s32 rl_steps){
  s32 steps = 0;
  
  if(fr_steps){
    #ifndef FR_REVERSE_DIR
      if(fr_steps > 0){
        DEBUG_PRINTLN("DEBUG: fr_motor -> FORWARD");
        digitalWrite(M_FR_DIR, HIGH);
      }
      else{
        DEBUG_PRINTLN("DEBUG: fr_motor -> BACKWARD");
        digitalWrite(M_FR_DIR, LOW);
      }
    #else
      if(fr_steps > 0){
        DEBUG_PRINTLN("DEBUG: fr_motor -> FORWARD");
        digitalWrite(M_FR_DIR, LOW);
      }
      else{
        DEBUG_PRINTLN("DEBUG: fr_motor -> BACKWARD");
        digitalWrite(M_FR_DIR, HIGH);
      }
    #endif
    steps = abs(fr_steps);
  }

  
  if(fl_steps){
    #ifndef FL_REVERSE_DIR
      if(fl_steps > 0){
        DEBUG_PRINTLN("DEBUG: fl_motor -> FORWARD");
        digitalWrite(M_FL_DIR, HIGH);
      }
      else{
        DEBUG_PRINTLN("DEBUG: fl_motor -> BACKWARD");
        digitalWrite(M_FL_DIR, LOW);
      }
    #else
      if(fl_steps > 0){
        DEBUG_PRINTLN("DEBUG: fl_motor -> FORWARD");
        digitalWrite(M_FL_DIR, LOW);
      }
      else{
        DEBUG_PRINTLN("DEBUG: fl_motor -> BACKWARD");
        digitalWrite(M_FL_DIR, HIGH);
      }
    #endif
    steps = abs(fl_steps);
  }

  
  if(rr_steps){
    #ifndef RR_REVERSE_DIR
      if(rr_steps > 0){
        DEBUG_PRINTLN("DEBUG: rr_motor -> FORWARD");
        digitalWrite(M_RR_DIR, HIGH);
      }
      else{
        DEBUG_PRINTLN("DEBUG: rr_motor -> BACKWARD");
        digitalWrite(M_RR_DIR, LOW);
      }
    #else
      if(rr_steps > 0){
        DEBUG_PRINTLN("DEBUG: rr_motor -> FORWARD");
        digitalWrite(M_RR_DIR, LOW);
      }
      else{
        DEBUG_PRINTLN("DEBUG: rr_motor -> BACKWARD");
        digitalWrite(M_RR_DIR, HIGH);
      }
    #endif
    steps = abs(rr_steps);
  }
  
  if(rl_steps){
    #ifndef RL_REVERSE_DIR
      if(rl_steps > 0){
        DEBUG_PRINTLN("DEBUG: rl_motor -> FORWARD");
        digitalWrite(M_RL_DIR, HIGH);
      }
      else{
        DEBUG_PRINTLN("DEBUG: rl_motor -> BACKWARD");
        digitalWrite(M_RL_DIR, LOW);
      }
    #else
      if(rl_steps > 0){
        DEBUG_PRINTLN("DEBUG: rl_motor -> FORWARD");
        digitalWrite(M_RL_DIR, LOW);
      }
      else{
        DEBUG_PRINTLN("DEBUG: rl_motor -> BACKWARD");
        digitalWrite(M_RL_DIR, HIGH);
      }
    #endif
    steps = abs(rl_steps);
  }
 
  /*Indicator to the User that the motion has been started*/
  DEBUG_PRINT("DEBUG: start moving ");
  DEBUG_PRINTLN((long)steps);

  total_steps = steps;
  n = 0;
  d = 50000;
  step_count = 0;
  ramp_up_step_count = 0;
  
  /*wait until the end of the motion*/
  while(steps){
    if(fr_steps) digitalWrite(M_FR_STEP, HIGH);
    if(fl_steps) digitalWrite(M_FL_STEP, HIGH);
    if(rr_steps) digitalWrite(M_RR_STEP, HIGH);
    if(rl_steps) digitalWrite(M_RL_STEP, HIGH);

    digitalWrite(M_FR_STEP, LOW);
    digitalWrite(M_FL_STEP, LOW);
    digitalWrite(M_RR_STEP, LOW);
    digitalWrite(M_RL_STEP, LOW);

    delayMicroseconds(calculate_delay_with_accel());
    steps--;
  }

  /*Indicator to the User that the motion has been finished and ERROR Status for Each motor*/
  DEBUG_PRINTLN("\nDEBUG: end moving\n");
  
}

/****************************************************      Private Functions   ****************************************************************************************/
/********  Motors Pins Configurations    ************/
void config_motors_pins(void){
  
  pinMode(M_FR_DIR, OUTPUT);
  pinMode(M_FR_STEP, OUTPUT);

  pinMode(M_FL_DIR, OUTPUT);
  pinMode(M_FL_STEP, OUTPUT);

  pinMode(M_RR_DIR, OUTPUT);
  pinMode(M_RR_STEP, OUTPUT);

  pinMode(M_RL_DIR, OUTPUT);
  pinMode(M_RL_STEP, OUTPUT);

  DEBUG_PRINT("DEBUG: Motors Config Max speed");
  DEBUG_PRINTLN(MOTORS_SPEED_uS);
  
}


/******** Define The motors Direction and Start Moving to the target   **********/
ISR(TIMER2_COMPA_vect){

  static u8 step_high_flag = 1;
  
  //Set The diection of each Motor
  if(!step_high_flag){
    
    #ifndef FR_REVERSE_DIR
      if(fr_target > enc_fr_position) fr_dir = 1;
      else fr_dir = 0;
    #else
      if(fr_target > enc_fr_position) fr_dir = 0;
      else fr_dir = 1;
    #endif
    
    #ifndef FL_REVERSE_DIR
      if(fl_target > enc_fl_position) fl_dir = 1;
      else fl_dir = 0;
    #else
      if(fl_target > enc_fl_position) fl_dir = 0;
      else fl_dir = 1;
    #endif
    
    #ifndef RR_REVERSE_DIR
      if(rr_target > enc_rr_position) RR_DIR_HIGH;
      else RR_DIR_LOW;
    #else
      if(rr_target > enc_rr_position) RR_DIR_LOW;;
      else RR_DIR_HIGH;
    #endif
    
    #ifndef RL_REVERSE_DIR
      if(rl_target > enc_rl_position) RL_DIR_HIGH;
      else RL_DIR_LOW;
    #else
      if(rl_target > enc_rl_position) RL_DIR_LOW;
      else RL_DIR_HIGH;
    #endif

    // take steps until the target 
    if(abs(fr_target - enc_fr_position) >= ENC_ERROR_MIN) do_semi_step(M_FR_STEP, M_FR_DIR, fr_dir);
    if(abs(fl_target - enc_fl_position) >= ENC_ERROR_MIN) do_semi_step(M_FL_STEP, M_FL_DIR, fl_dir);
    if(abs(rr_target - enc_rr_position) >= ENC_ERROR_MIN) RR_STEP_HIGH;
    if(abs(rl_target - enc_rl_position) >= ENC_ERROR_MIN) RL_STEP_HIGH;
    
    step_high_flag = 0;
  }else{
    
    RR_STEP_LOW;
    RL_STEP_LOW;

    step_high_flag = 1;
  }
}

/***** Steper Motors Closed Loop Initialization  ******/
void closed_loop_steppers_init(void){
  config_motors_pins();
  config_encoders_pins();
  
  TCCR2A = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TCCR2B = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TIMSK2 |= (1 << OCIE2A);                                                  //Set the interupt enable bit OCIE2A in the TIMSK2 register
  TCCR2B |= ((1 << CS21) | (1 << CS22));                                    //Set the CS21 bit in the TCCRB register to set the prescaler to 256
  OCR2A = (16 / 256)*(MOTORS_SPEED_uS / 2);                                 //The compare register is set to 250 => 4ms / (1s / (16.000.000MHz / 256))
  TCCR2A |= (1 << WGM21);                                                   //Set counter 2 to CTC (clear timer on compare) mode
  
  enc_fr_position = 0;
  enc_fl_position = 0;
  enc_rr_position = 0;
  enc_rl_position = 0;
  fr_target = 0;
  fl_target = 0;
  rr_target = 0;
  rl_target = 0;
  
  /*Call the ISR of the steper motor periodically*/
  DEBUG_PRINTLN("DEBUG: Start Closed-loop Stepper motor");
  DEBUG_PRINT("DEBUG: Loop Refresh Rate is every ");
  DEBUG_PRINT((long)(MOTORS_SPEED_uS/2));
  DEBUG_PRINTLN(" uS");
  
}

void do_semi_step(u8 step_pin, u8 dir_pin, u8 dir){
  //DEBUG_PRINTLN(F("PP"));
  digitalWrite(dir_pin, dir);
  digitalWrite(step_pin, HIGH);
}

/**************************************************************************************************/
/* OUTPUT: 1 means => Can moveing
 *         0 means => Can't Moveing
*/
bool can_step(s32 target, s32 current){
  u32 e = abs(target - current);
  if(e <= ENC_ERROR_MIN) return 0;
  else return 1;
}
