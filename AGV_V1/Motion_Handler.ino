/**************************************************************/
/***********     Author    :                         **********/
/***********     File Name :  Motion_Handler         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  02-05-2021             **********/
/***********     Function  :                         **********/
/**************************************************************/
/*
 * Robot Wheels:
 *                       X
 *                       ^
 *                       |
 *                   Y ---
 *                    _______
 *     1- fl_wheel  -|       |-  2-fr_wheel
 *                   |       |
 *                   |       |
 *     3- rl_wheel  -|_______|-  4-rr_wheel
 * 
 * (0, 50, 0)->(100, 100, 0)
 */
#define KINEMATICS_F32_RAD_TO_NUM_OF_STEPS(TARGET_RAD)     (round(TARGET_RAD * MOTORS_PPR /(2 * PI)))


/****************************************************************/
/***************   Interface Functions  *************************/
/****************************************************************/
void KINEMATICS_vidGoAbsCoordinates(s32 Cpy_s32TargetX,s32 Cpy_s32TargetY,s16 Cpy_s16TargetTheta)
{
  DEBUG_PRINTLN("DEBUG: Go TO (XY Plane)");
  DEBUG_PRINT("DEBUG:  X = "); DEBUG_PRINT(Cpy_s32TargetX); DEBUG_PRINTLN(" mm");
  DEBUG_PRINT("DEBUG:  Y = "); DEBUG_PRINT(Cpy_s32TargetY); DEBUG_PRINTLN(" mm");
  DEBUG_PRINT("DEBUG:  θ = "); DEBUG_PRINT(Cpy_s16TargetTheta); DEBUG_PRINTLN(" deg");
  DEBUG_PRINTLN("DEBUG: ------------- Start Move -------------");
  
  /*Declare Some essencial Variables*/
  s8 Loc_s8Temp=0;
  u8 Loc_u8CorrectX = 1 , Loc_u8CorrectY = 1 , Loc_u8CorrectTheta = 1 , Loc_u8ForceCorrectionEnd = 0 ;

  /*Update Absolute target*/
  KINEMATICS_s32TargetX       = Cpy_s32TargetX;
  KINEMATICS_s32TargetY       = Cpy_s32TargetY;
  KINEMATICS_f32TargetTheta   = Cpy_s16TargetTheta;

  /*Measure Current Position*/
  //KINEMATICS_vidCalcCurrentPosition();

  /*Calculate Target Relative to current position. */
  Cpy_s32TargetX      = KINEMATICS_s32TargetX      - KINEMATICS_f32CurrentXPosition;
  Cpy_s32TargetY      = KINEMATICS_s32TargetY      - KINEMATICS_f32CurrentYPosition;
  Cpy_s16TargetTheta  = KINEMATICS_f32TargetTheta  - KINEMATICS_f32CurrentTheta;
  

  /*Check Diagonal motion. if yes, determine the corner*/
  if (Cpy_s32TargetY != 0) {Loc_s8Temp = Cpy_s32TargetX/Cpy_s32TargetY;}  //reltive target must be integer
  switch (Loc_s8Temp)
  {
    case  1 : if (Cpy_s32TargetX>0) {KINEMATICS_vidSquareDiameterMove( Cpy_s32TargetX,1);} 
              else                  {KINEMATICS_vidSquareDiameterMove(-Cpy_s32TargetX,4);} break;
    case -1 : if (Cpy_s32TargetX<0) {KINEMATICS_vidSquareDiameterMove( Cpy_s32TargetY,3);}
              else                  {KINEMATICS_vidSquareDiameterMove( Cpy_s32TargetX,2);} break;
    default : Loc_s8Temp=0;                                                                break;
  }

  /*if diagonal motion is not possible, move sidey*/
  if (Loc_s8Temp==0)
  {
    if(Cpy_s32TargetX) KINEMATICS_vidMoveXAxis(Cpy_s32TargetX);
    if(Cpy_s32TargetY) KINEMATICS_vidMoveYAxis(Cpy_s32TargetY);
  }
   
  /*Rotate yaw angle*/
  KINEMATICS_vidRotateZAxis(Cpy_s16TargetTheta);

  //KINEMATICS_vidCalcCurrentPosition();
  KINEMATICS_f32CurrentXPosition = KINEMATICS_s32TargetX;
  KINEMATICS_f32CurrentYPosition = KINEMATICS_s32TargetY;
  KINEMATICS_f32CurrentTheta = KINEMATICS_f32TargetTheta;
  
  
  /*Check and fix the ERROR*/
//  while(Loc_u8CorrectX == 1 || Loc_u8CorrectY == 1 || Loc_u8CorrectTheta == 1 )
//  {
//  KINEMATICS_vidCalcCurrentPosition();
//      
//  Loc_s8Temp = abs (KINEMATICS_s32TargetX - KINEMATICS_f32CurrentXPosition);
//  if (Loc_s8Temp>KINEMATICS_MX_LIN_ERR)  {KINEMATICS_vidMoveXAxis(KINEMATICS_s32TargetX-KINEMATICS_f32CurrentXPosition);}
//  else { Loc_u8CorrectX--;}
//
//  Loc_s8Temp = abs (KINEMATICS_s32TargetY - KINEMATICS_f32CurrentYPosition);
//  if (Loc_s8Temp>KINEMATICS_MX_LIN_ERR)  {KINEMATICS_vidMoveYAxis(KINEMATICS_s32TargetY-KINEMATICS_f32CurrentYPosition);}
//  else { Loc_u8CorrectY--;}
//  
//  Loc_s8Temp = abs (Cpy_s16TargetTheta - KINEMATICS_f32CurrentTheta);
//  if (Loc_s8Temp>KINEMATICS_MX_THETA_ERR)  {KINEMATICS_vidMoveYAxis(Cpy_s16TargetTheta-KINEMATICS_f32CurrentYPosition);}
//  else { Loc_u8CorrectTheta--;}
//
//  Loc_u8ForceCorrectionEnd++;
//  if (Loc_u8ForceCorrectionEnd == 5) {break;}
//  }

  DEBUG_PRINTLN("DEBUG: -------------- End Move --------------");
  DEBUG_PRINT("DEBUG:  X = "); DEBUG_PRINT(KINEMATICS_f32CurrentXPosition); DEBUG_PRINTLN(" mm");
  DEBUG_PRINT("DEBUG:  Y = "); DEBUG_PRINT(KINEMATICS_f32CurrentYPosition); DEBUG_PRINTLN(" mm");
  DEBUG_PRINT("DEBUG:  θ = "); DEBUG_PRINT(KINEMATICS_f32CurrentTheta); DEBUG_PRINTLN(" deg");
  DEBUG_PRINTLN("DEBUG: -------------- -------- --------------");

} //FUNC END




/****************************************************************/
/****************   Helping Functions     ***********************/
/****************************************************************/
/*1- ******************************************************************************************************************************************************************************
 * INPUTS       : Distance along X axis in mm, can be positive or negative
 * Note!        : 1-All Wheels will take the same motion 
 * ERROR Indic  : The max. numb. of steps that may be neglected = 1 step:
 *                  if the steper takes 800 SPR then each step will rotate 0.45 degree = 0.0078 Rad
 *                  if the wheel radius 60mm then each step will move (RAD*RADUIS)=0.468 mm    
 *               in this case the error will be <= 0.468mm
 */
void KINEMATICS_vidMoveXAxis(s32 Cpy_s32TargetX)
{
  /*Define Required Variables*/
  f32  Loc_f32TargetRad =0;

  /*Calculate the Required angular displacement to reach the target X point*/
  Loc_f32TargetRad = KINEMATICS_s32TargetX / WHEEL_RADIUS_mm ;

  /*Convert Target Rad To Number of Steps*/
  Loc_f32TargetRad = KINEMATICS_F32_RAD_TO_NUM_OF_STEPS(Loc_f32TargetRad);

  /*Send the values to the stepper mototrs*/
  run_motors_steps(Loc_f32TargetRad, Loc_f32TargetRad, Loc_f32TargetRad, Loc_f32TargetRad);
}

/*2- ****************************************************************************************************************************************************************************
 * INPUTS       : Distance along Y axis in mm, can be positive or negative
 * Note!        : 1-To move on Positive Y: Wheels 2,3 will move forward at the same speed, 
 *                                     and Wheels 1.4 will move backward at the same speed of 2,3
 * Kinematics   : θ1 = θ4 = -y/radius , θ2 = θ3 = y/radius                                                                 
 * ERROR Indic  : The max. numb. of steps that may be neglected = 1 step:
 *                  if the steper takes 800 SPR then each step will rotate 0.45 degree = 0.0078 Rad
 *                  if the wheel radius 60mm then each step will move (RAD*RADUIS)=0.468 mm    
 *                in this case the error will be <= 0.468mm
 */
void KINEMATICS_vidMoveYAxis(s32 Cpy_s32TargetY)
{
  /*Define Required Variables*/
  f32  Loc_f32TargetRad =0;

  /*Calculate the Required angular displacement to reach the target Y point*/
  Loc_f32TargetRad = KINEMATICS_s32TargetY / WHEEL_RADIUS_mm ;

  /*Convert Target Rad To Number of Steps*/
  Loc_f32TargetRad = KINEMATICS_F32_RAD_TO_NUM_OF_STEPS(Loc_f32TargetRad);
  
  /*Send the values to the stepper mototrs*/
  run_motors_steps(Loc_f32TargetRad, -1*Loc_f32TargetRad, -1*Loc_f32TargetRad, Loc_f32TargetRad);

  DEBUG_PRINTLN("DEBUG: KINEMATICS_vidMoveYAxis");
}

/*3- ****************************************************************************************************************************************************************************
 * INPUTS       : Rotation about Z axis in Degrees, can be positive or negative.
 * Kinematics   : Wheel Angular Displacement(rad) = (lx+ly)/r * Orintation(deg) 
 *                -To Rotate CCW: Wheels 2,4 will move forward at the same speed, 
 *                            and Wheels 1,3 will move backward at the same speed of 2,4 
 * Note!        : 1-Theta value is recommended to be from -180 to 180.
 *                2-Any fraction of a degree will not be neglected
 *                                                         
 * ERROR        : The max. numb. of steps that may be neglected = 1 step:
 *                  if the stepper takes 800 SPR then each step will rotate the wheel 0.45 degree = 0.0078 Rad
 *                  if the wheel radius 60mm, and lx+ly= 100 mm, then each step will rotate (RAD*RADUIS/(lx+ly)) = 0.00468 rad = 0.2681 degree    
 *                With these assumptions the error will be <= 0.2681 degree
 *                   the greater lx and ly will be, the less error will be occurred
 *                   the greater the raduis is, More error will be occurred
 */
void KINEMATICS_vidRotateZAxis(f32 Cpy_f32TargetTheta)
{

  /*Convert Target Theta from degrees to radians*/
  Cpy_f32TargetTheta = Cpy_f32TargetTheta * PI / 180 ;

  /*Apply the equation to obtain the angular displacement of the wheels*/
  Cpy_f32TargetTheta = Cpy_f32TargetTheta * WHEEL_LX_PLUS_LY / WHEEL_RADIUS_mm ;
                     
  /*Convert the target rad of the wheel into steps*/
  Cpy_f32TargetTheta = KINEMATICS_F32_RAD_TO_NUM_OF_STEPS(Cpy_f32TargetTheta);

  /*Send the values to the stepper mototrs*/
  run_motors_steps(Cpy_f32TargetTheta, -Cpy_f32TargetTheta, Cpy_f32TargetTheta, -Cpy_f32TargetTheta);

  DEBUG_PRINTLN("DEBUG: KINEMATICS_vidRotateZAxis");
}



 /*4- ****************************************************************************************************************************************************************************
 * Description  : This function is used to move the robot obliquely with theta 45, that means this motion is just a specific case of obliquely motion. 
 *                    this is the only case of obplique motion that doesn't require a defferent speed for each wheel
 * INPUTS       : 1-Square side in mm  (positive)
 *                2-the number of the conrer only can be integer numbers from 1 to 4.
 * Kinematics   : Wheel Angular Displacement(Theta)(rad) = 2/r * Square_diameter_lenth
 *                  Corner One   : Wheels 2,3 forwards, and stop 1,4 wheels
 *                  Corner Two   : Wheels 1,4 forwards, and stop 2,3 wheels
 *                  Corner Three : Wheels 1,4 backward, and stop 2,3 wheels
 *                  Corner Four  : Wheels 2,3 backward, and stop 1,4 wheels
 *                                                         
 * ERROR        : The max. numb. of steps that may be neglected = 1 step:
 *                  if the stepper takes 800 SPR then each step will rotate the wheel 0.45 degree = 0.0078 Rad
 *                  if the wheel radius 60mm, and lx+ly= 100 mm, then each step will rotate (RAD*RADUIS/(lx+ly)) = 0.00468 rad = 0.2681 degree    
 *                With these assumptions the error will be <= 0.2681 degree
 *                   the greater lx and ly will be, the less error will be occurred
 *                   the greater the raduis is, More error will be occurred
 */
void KINEMATICS_vidSquareDiameterMove(f32 Cpy_f32SquareSide, u8 Cpy_u8CornerNumb )
{

  /*Range Check*/
  if (Cpy_f32SquareSide<0) {Cpy_f32SquareSide *= -1;}
  
  /*Apply kinematics to calc the theta of the wheels*/
  Cpy_f32SquareSide = 2 * Cpy_f32SquareSide / WHEEL_RADIUS_mm;

  /*Convert the target rad of the wheel into steps*/
  Cpy_f32SquareSide = KINEMATICS_F32_RAD_TO_NUM_OF_STEPS(Cpy_f32SquareSide);

  /*Send the values to the stepper mototrs*/
  switch (Cpy_u8CornerNumb)
  {
   case 1: run_motors_steps(    Cpy_f32SquareSide, 0, 0, Cpy_f32SquareSide   );   break;
   case 2: run_motors_steps(0,  Cpy_f32SquareSide,       Cpy_f32SquareSide, 0);   break;
   case 3: run_motors_steps(0, -Cpy_f32SquareSide,      -Cpy_f32SquareSide, 0);   break;
   case 4: run_motors_steps(   -Cpy_f32SquareSide, 0, 0,-Cpy_f32SquareSide   );   break;
  } //END Switch

  DEBUG_PRINTLN("DEBUG: KINEMATICS_vidSquareDiameterMove");
  
} //END Func



/*5- ****************************************************************************************************************************************************************************
 * Kinematics   : Wheel_Anguar_displacement = Wheel_Enc *(2 * PI / ENCODERS_PPR)
 *                  X_Position    = ( θ1 + θ2 + θ3 + θ4) * (Wheel_Rduis / 4)
 *                  Y_Position    = (-θ1 + θ2 + θ3 - θ4) * (Wheel_Rduis / 4)
 *                  Theta_Postion = (-θ1 + θ2 - θ3 + θ4) * (Wheel_Rduis / 4) / (Lx + Ly)
 */
void KINEMATICS_vidCalcCurrentPosition(void)
{
  /*Forward kinematics, Calc the current absolute position*/
  KINEMATICS_f32CurrentXPosition = (  enc_fl_position+enc_fr_position + enc_rl_position+enc_rr_position) *(2 * PI / ENCODERS_PPR) * (WHEEL_RADIUS_mm / 4);
  KINEMATICS_f32CurrentYPosition = (- enc_fl_position+enc_fr_position + enc_rl_position-enc_rr_position) *(2 * PI / ENCODERS_PPR) * (WHEEL_RADIUS_mm / 4);
  KINEMATICS_f32CurrentTheta     = (- enc_fl_position+enc_fr_position - enc_rl_position+enc_rr_position) *(2 * PI / ENCODERS_PPR) * (WHEEL_RADIUS_mm /(4 * WHEEL_LX_PLUS_LY ));
  KINEMATICS_f32CurrentTheta    *= 180 / PI;
  //IMU_angle_yaw_output
  while (KINEMATICS_f32CurrentTheta > 180) {KINEMATICS_f32CurrentTheta -= 360;}
  while (KINEMATICS_f32CurrentTheta <-180) {KINEMATICS_f32CurrentTheta += 360;}

  DEBUG_PRINTLN("DEBUG: KINEMATICS_vidCalcCurrentPosition");
}

//void KINEMATICS_vidObliquely(u8 Lenth, u8 Theta );
