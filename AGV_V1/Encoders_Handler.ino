/* Green = A phase 
 * White = B phase
 *    _____       _____
 *   |  :  |     |     |
 * A |  :  |_____|     |_____
 *   :  :
 *   :  :
 *   :  :_____       _____
 *   :  |     |     |     |
 * B :__|     |_____|     }___
 *   :  :
 *   :  :
 *   v  v
 *   -90-
 *   
 *   
 */
volatile bool f = false;
void config_encoders_pins(void){
  
  pinMode(ENC_A_FR, INPUT_PULLUP);
  pinMode(ENC_B_FR, INPUT_PULLUP);
  
  pinMode(ENC_A_FL, INPUT_PULLUP);
  pinMode(ENC_B_FL, INPUT_PULLUP);
  
  pinMode(ENC_A_RR, INPUT_PULLUP);
  pinMode(ENC_B_RR, INPUT_PULLUP);
  
  pinMode(ENC_A_RL, INPUT_PULLUP);
  pinMode(ENC_B_RL, INPUT_PULLUP);

  #ifdef ENCODER_PHASE_2
    attachInterrupt(digitalPinToInterrupt(ENC_A_RL), isr_enc_rear_left, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_A_RR), isr_enc_rear_right, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_A_FL), isr_enc_front_left, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_A_FR), isr_enc_front_right, CHANGE);
    DEBUG_PRINTLN("DEBUG: Encoders Configuration as 1200 PPR");
  #else
    attachInterrupt(digitalPinToInterrupt(ENC_A_RL), isr_enc_rear_left, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_A_RR), isr_enc_rear_right, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_A_FL), isr_enc_front_left, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_A_FR), isr_enc_front_right, RISING);
    DEBUG_PRINTLN("DEBUG: Encoders Configuration as 600 PPR");
  #endif

}

void isr_enc_front_right(void){
  #ifdef ENCODER_PHASE_2
    if(digitalRead(ENC_A_FR) == digitalRead(ENC_B_FR)) enc_fr_position--;
    else enc_fr_position++;
  #else
    if(digitalRead(ENC_B_FR)) enc_fr_position--;
    else enc_fr_position++;
  #endif
  f = true;
}

void isr_enc_front_left(void){
  #ifdef ENCODER_PHASE_2
    if(digitalRead(ENC_A_FL) == digitalRead(ENC_B_FL)) enc_fl_position--;
    else enc_fl_position++;
  #else
    if(digitalRead(ENC_B_FL)) enc_fl_position--;
    else enc_fl_position++;
  #endif
  f = true;
}

void isr_enc_rear_right(void){
  #ifdef ENCODER_PHASE_2
    if(digitalRead(ENC_A_RR) == digitalRead(ENC_B_RR)) enc_rr_position--;
    else enc_rr_position++;
  #else
    if(digitalRead(ENC_B_RR)) enc_rr_position--;
    else enc_rr_position++;
  #endif
  f = true;
}

void isr_enc_rear_left(void){
  #ifdef ENCODER_PHASE_2
    if(digitalRead(ENC_A_RL) == digitalRead(ENC_B_RL)) enc_rl_position--;
    else enc_rl_position++;
  #else
    if(digitalRead(ENC_B_RL)) enc_rl_position--;
    else enc_rl_position++;
  #endif
  f = true;
}
