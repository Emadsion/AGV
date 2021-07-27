#ifndef DEF_H
#define DEF_H


/*Include all the used libraries*/
#include <SPI.h>
#include <MFRC522.h>

#define DEBUG


/*Define datatypes*/
typedef uint8_t   u8;
typedef int8_t    s8;
typedef unsigned short u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;
typedef float    f32;
typedef double   f64;

//#define FR_REVERSE_DIR
//#define FL_REVERSE_DIR
//#define RR_REVERSE_DIR
//#define RL_REVERSE_DIR

//#define ENCODER_PHASE_2 

/* Prototypes of All interface Functions*/

/*******************  Pins and Data Configurations  ***********************************/
///////////////////////////
// 1-Encoders
//////////////////////////
#define ENC_B_FR  4
#define ENC_A_FR  2
#define ENC_B_FR_REG  ((PIOC->PIO_PDSR & PIO_PC13) == PIO_PC13)
#define ENC_A_FR_REG  ((PIOC->PIO_PDSR & PIO_PC15) == PIO_PC15)

#define ENC_A_FL  3
#define ENC_B_FL  5
#define ENC_A_FL_REG  (PIOC->PIO_PDSR & PIO_PC19)
#define ENC_B_FL_REG  (PIOC->PIO_PDSR & PIO_PC17)

#define ENC_B_RR  18
#define ENC_A_RR  19
#define ENC_B_RR_REG  (PIOC->PIO_PDSR & PIO_PC8)
#define ENC_A_RR_REG  (PIOC->PIO_PDSR & PIO_PC6)

#define ENC_A_RL  20
#define ENC_B_RL  21
#define ENC_A_RL_REG  (PIOC->PIO_PDSR & PIO_PC2)
#define ENC_B_RL_REG  (PIOC->PIO_PDSR & PIO_PC4)


#ifdef ENCODER_PHASE_2
  #define ENCODERS_PPR   1200.0
#else
  #define ENCODERS_PPR   600.0
#endif

#define MASK(x) (1 << x)

#define ENC_ERROR_MIN  10
//////////////////////////////////

//////////////////////////////////
// 2-Motors
//////////////////////////////////
#define M_FR_DIR     51   //PC12
#define M_FR_STEP    49   //PC14
#define FR_DIR_HIGH  PIOC -> PIO_SODR = PIO_SODR_P12
#define FR_DIR_LOW   PIOC -> PIO_CODR = PIO_CODR_P12
#define FR_STEP_HIGH PIOC -> PIO_SODR = PIO_SODR_P14
#define FR_STEP_BIT  PIO_CODR_P14

#define M_FL_DIR     47   //PC16
#define M_FL_STEP    45   //PC18
#define FL_DIR_HIGH  PIOC -> PIO_SODR = PIO_SODR_P16
#define FL_DIR_LOW   PIOC -> PIO_CODR = PIO_CODR_P16
#define FL_STEP_HIGH PIOC -> PIO_SODR = PIO_SODR_P18
#define FL_STEP_BIT  PIO_CODR_P18

#define M_RR_DIR     41   //PG0
#define M_RR_STEP    39   //PG2
#define RR_DIR_HIGH  (PORTG |=  (1 << 0))
#define RR_DIR_LOW   (PORTG &= ~(1 << 0))
#define RR_STEP_HIGH (PORTG |=  (1 << 2))
#define RR_STEP_LOW  (PORTG &= ~(1 << 2))

#define M_RL_DIR     37   //PC0
#define M_RL_STEP    35   //PC2
#define RL_DIR_HIGH  (PORTC |=  (1 << 0))
#define RL_DIR_LOW   (PORTC &= ~(1 << 0))
#define RL_STEP_HIGH (PORTC |=  (1 << 2))
#define RL_STEP_LOW  (PORTC &= ~(1 << 2))

#define MOTORS_FULL_STEPS   200.0
#define MOTORS_MICROSTEPS   4.0
#define MOTORS_SPEED_RPM    20   // rpm
#define MOTORS_PPR          (MOTORS_FULL_STEPS * MOTORS_MICROSTEPS)
//#define MOTORS_SPEED_uS     (1000000 /((MOTORS_SPEED_RPM  / 60.0) * MOTORS_PPR))
#define MOTORS_SPEED_uS     1000

//////////////////////////////////

//////////////////////////////////
// 3- Wheels
//////////////////////////////////
#define WHEEL_RADIUS_mm        62.5
/*****************************************************************************
 * Following values won't affect the translational motion of the ROBOT.
 * where : Lx is the half of the distance between front wheels
 *         Ly is the half of the distance between front wheels and rear wheels
 */
#define WHEEL_LX              175.0  // mm 
#define WHEEL_LY              195.0  // mm
#define WHEEL_LX_PLUS_LY     (WHEEL_LX + WHEEL_LY)

/////////////////////////////////////

//////////////////////////////////
// 4- IMU
//////////////////////////////////
#define IMU_HZ       250
/////////////////////////////////////

//////////////////////////////////
// 5- Ultrasonic sensors
//////////////////////////////////
#define STRAIGHT_MIN_LIMIT  75.0
#define DIAGONAL_MIN_LIMIT  106.0

#define FRONT_TRIG 2
#define FRONT_ECHO 3

#define REAR_TRIG  4
#define REAR_ECHO  5

#define RIGHT_TRIG 6
#define RIGHT_ECHO 7

#define LEFT_TRIG  8
#define LEFT_ECHO  9

#define FR_TRIG    10
#define FR_ECHO    11

#define FL_TRIG    12
#define FL_ECHO    13

#define RR_TRIG    31
#define RR_ECHO    29

#define RL_TRIG    25
#define RL_ECHO    23

enum{FRONT, REAR, RIGHT, LEFT, FRONT_RIGHT, FRONT_LEFT, REAR_RIGHT, REAR_LEFT};
/////////////////////////////////////

//////////////////////////////////
// 6- RFID reders
//////////////////////////////////
#define SS_MAP     4   //youssef might change them. 
#define RST_MAP    7  
#define SS_OBJ     10
#define RST_OBJ    8

MFRC522 rfid_map(SS_MAP, RST_MAP);   // Create  instance.
MFRC522 rfid_obj(SS_OBJ, RST_OBJ);   

MFRC522::MIFARE_Key key;   //using factory default key for all readers and cards.

/////////////////////////////////////

//////////////////////////////////
// 6- RFID reders
//////////////////////////////////
#define LIFT_M_STEP        27
#define LIFT_M_DIR         29

#define LIFT_M_MICROSTEPS  8.0
#define LIFT_M_PPR         (200 * LIFT_M_MICROSTEPS)

/////////////////////////////////////

#define KINEMATICS_MX_LIN_ERR 5
#define KINEMATICS_MX_THETA_ERR 5
/* Prototypes of All interface Functions*/



#ifdef DEBUG
  #define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTLN(...)
#endif


//Global Variables
/*never to initialize global variable, that will save the space in the flash*/

volatile s32 enc_fr_position, enc_fl_position, enc_rr_position, enc_rl_position;
volatile s32 fr_target, fl_target,rr_target, rl_target;
volatile u8 fr_dir, fl_dir, rr_dir, rl_dir;

f32 d;
s32 n, step_count, ramp_up_step_count, total_steps;

/*MOTION_HANDLER*/
f32 KINEMATICS_f32CurrentXPosition, KINEMATICS_f32CurrentYPosition, KINEMATICS_f32CurrentTheta; 
s32 KINEMATICS_s32TargetX,KINEMATICS_s32TargetY;
f32 KINEMATICS_f32TargetTheta;

/*IMU_HANDLER*/
s16 IMU_gyro_x, IMU_gyro_y, IMU_gyro_z;
s32 IMU_acc_x, IMU_acc_y, IMU_acc_z, IMU_acc_total_vector;
s16 temperature;
s32 IMU_gyro_x_cal, IMU_gyro_y_cal, IMU_gyro_z_cal;
f32 IMU_angle_pitch, IMU_angle_roll, IMU_angle_yaw;
u8 set_gyro_angles;
f32 IMU_angle_roll_acc, IMU_angle_pitch_acc;
f32 IMU_angle_pitch_output, IMU_angle_roll_output,IMU_angle_yaw_output;

/*RFID and Navigation*/
//flags
u8 problem_rfid_map;
u8 problem_rfid_obj;

u8 flag_obstacle;

//map
u8 first_loading_place = 8;   //changable 8 = 1,1 (index starts at 0)
u8 start_node; 
u8 end_node;

u16 x_loading; 
u16 y_unloading;

/* shortest path */

#define A        34
#define B        16
#define C        31
#define D        13
#define NO_NODES 48
#define INT_MAX  9999
#define MAP_PITCH_mm 750

/*
char MAP[8][6] = {
  {'1', '1', '1', '1', '1', '1'},
  {'a', '1', '1', '1', '1', '1'},
  {'1', 'D', '1', '1', 'B', '1'},
  {'1', '1', '1', '1', '1', '1'},
  {'1', '1', '1', '1', '1', '1'},
  {'1', 'C', '1', '1', 'A', '1'},
  {'1', '1', '1', '1', '1', '1'},
  {'1', '1', '1', '1', '1', '1'}
};
*/

//char Loading[4] = {'a', 'b', 'c', 'd'};
u8 Unloading[4] = {A , B, C, D};

u8 loadingPlace, unloadingPlace;
u8 Graph[NO_NODES][NO_NODES];
s8 shortest_path_nodes[NO_NODES];
u8 shortest_path_nodes_index;

#endif
