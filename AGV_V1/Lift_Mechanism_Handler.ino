
void cofig_lift_mechanism(void){
  pinMode(LIFT_M_STEP, OUTPUT);
  pinMode(LIFT_M_DIR, OUTPUT);
  DEBUG_PRINTLN("DEBUG: Lift mechanism Config");
  
}

s16 calculate_delay_with_accel(void){
  if (step_count < total_steps) step_count++;

  if (ramp_up_step_count == 0) {
    // ramp up phase
    n++;
    d = d - (2 * d) / (4 * n + 1);
    if (d <= MOTORS_SPEED_uS) {
      // reached max speed
      d = MOTORS_SPEED_uS;
      ramp_up_step_count = step_count;
      n++;
    }
    else if (step_count >= total_steps / 2) {
      // reached halfway point
      ramp_up_step_count = step_count;
      n++;
    }
  }
  else if (step_count > total_steps - ramp_up_step_count) {
    // ramp down phase
    n--;
    d = (d * (4 * n + 1)) / (abs(4 * n + 1 - 2));
  }
  return round(d);
}

void lift_object_mm(s16 height){
  s32 steps = height / 3.0 * LIFT_M_PPR;
  DEBUG_PRINT("DEBUG: lift_steps = ");
  DEBUG_PRINTLN(steps);
  if(steps > 0) digitalWrite(LIFT_M_DIR, LOW);
  else digitalWrite(LIFT_M_DIR, HIGH);

  total_steps = abs(steps);
  n = 0;
  d = 5000;
  step_count = 0;
  ramp_up_step_count = 0;
  
  for(s32 i = 0; i <= abs(steps); i++){
    digitalWrite(LIFT_M_STEP, HIGH);
    delayMicroseconds(3);
    digitalWrite(LIFT_M_STEP, LOW);
    delayMicroseconds(calculate_delay_with_accel() - 3);
  }
}
