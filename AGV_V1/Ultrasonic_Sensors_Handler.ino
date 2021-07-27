
void config_ultrasonic_sensors(void){
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);

  pinMode(REAR_TRIG, OUTPUT);
  pinMode(REAR_ECHO, INPUT);
  
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  pinMode(FR_TRIG, OUTPUT);
  pinMode(FR_ECHO, INPUT);

  pinMode(FL_TRIG, OUTPUT);
  pinMode(FL_ECHO, INPUT);

  pinMode(RR_TRIG, OUTPUT);
  pinMode(RR_ECHO, INPUT);

  pinMode(RL_TRIG, OUTPUT);
  pinMode(RL_ECHO, INPUT);
}

u8 is_there_obstacle(u8 dir){
  u32 _time = 0;
  u16 limit = 0;
  
  switch(dir){
    case FRONT:
      digitalWrite(FRONT_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(FRONT_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(FRONT_TRIG, LOW);
      _time = pulseIn(FRONT_ECHO, HIGH);
      limit = STRAIGHT_MIN_LIMIT;
      break;

    case REAR:
      digitalWrite(REAR_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(REAR_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(REAR_TRIG, LOW);
      _time = pulseIn(REAR_ECHO, HIGH);
      limit = STRAIGHT_MIN_LIMIT;
      break;

    case RIGHT:
      digitalWrite(RIGHT_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(RIGHT_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(RIGHT_TRIG, LOW);
      _time = pulseIn(RIGHT_ECHO, HIGH);
      limit = STRAIGHT_MIN_LIMIT;
      break;

    case LEFT:
      digitalWrite(LEFT_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(LEFT_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(LEFT_TRIG, LOW);
      _time = pulseIn(LEFT_ECHO, HIGH);
      limit = STRAIGHT_MIN_LIMIT;
      break;

    case FRONT_RIGHT:
      digitalWrite(FR_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(FR_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(FR_TRIG, LOW);
      _time = pulseIn(FR_ECHO, HIGH);
      limit = DIAGONAL_MIN_LIMIT;
      break;

    case FRONT_LEFT:
      digitalWrite(FL_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(FL_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(FL_TRIG, LOW);
      _time = pulseIn(FL_ECHO, HIGH);
      limit = DIAGONAL_MIN_LIMIT;
      break;

    case REAR_RIGHT:
      digitalWrite(RR_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(RR_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(RR_TRIG, LOW);
      _time = pulseIn(RR_ECHO, HIGH);
      limit = DIAGONAL_MIN_LIMIT;
      break;

    case REAR_LEFT:
      digitalWrite(RL_TRIG, LOW);  delayMicroseconds(5);
      digitalWrite(RL_TRIG, HIGH); delayMicroseconds(10);
      digitalWrite(RL_TRIG, LOW);
      _time = pulseIn(RL_ECHO, HIGH);
      limit = DIAGONAL_MIN_LIMIT;
      break;

    default: Serial.println("DEBUG: fault direction send to: is_there_obstacle();");
  }

  f32 dis  = _time * 0.017525;

  if(dis <= limit) return true;
  else false;
}
