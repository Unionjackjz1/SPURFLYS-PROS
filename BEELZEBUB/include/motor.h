/* header guard */
#ifndef MOTOR_H_
#define MOTOR_H_

// Include function prototypes
#include "main.h"

//#define ARM_L1    2 /* FALSE */
//#define ARM_L2    3 /* FALSE */
//#define MOGO_L    4 /* FALSE */
//#define CHASSIS_L 5 /* FALSE */
//#define MOGO_R    6 /* TRUE */
//#define CHASSIS_R 7 /* TRUE */
//#define ARM_R1    8 /* FALSE */
//#define ARM_R2    9 /* TRUE */

/**
 * Motor names
 */
 #define ARM_L1    2 /* FALSE */
 #define ARM_L2    3 /* FALSE */
 #define MOGO_L    4 /* FALSE */
 #define CHASSIS_L 5 /* FALSE */
 #define MOGO_R    6 /* TRUE */
 #define CHASSIS_R 7 /* TRUE */
 #define ARM_R1    8 /* FALSE */
 #define ARM_R2    9 /* TRUE */

/**
 * Sensor value for arm
 *
 * @return	Current sensor value
 */
int getArmSensor();

/**
 * Sensor value for mogo lift
 *
 * @return	Current sensor value
 */
int getMogoSensor();

/**
 * Sensor value for right chassis
 *
 * @return	Current sensor value
 */
int getRightChassisSensor();

/**
 * Sensor value for left chassis
 *
 * @return	Current sensor value
 */
int getLeftChassisSensor();

/**
 * Defines for chassis IME's
 */
 #define RIGHT_CHASSIS_IME 0
 #define LEFT_CHASSIS_IME  1
 #define NUMBER_OF_IME     2

/**
 * Struct for motor seutp
 *
 * @param  bReverse    Sets inverted power to motor
 * @param  bTruespeed  Sets linear RPM curve to motor
 */
typedef struct _motor{
  bool bReverse;
  bool bTruespeed;
}enMotor;

/**
 * Struct for easy PID
 *
 * @param  current     Current position
 * @param  kP          Constant proportional term
 * @param  KD          Constant derivative term
 * @param  target      Target position
 * @param  error       Target (-) Current
 * @param  derivative  Predicts future trends in the error
 * @param  lastError   Last error... its in the name <3
 */
typedef struct {
	float current;
	float kP;
	float kD;
	float target;
	float error;
	float derivative;
	float lastError;
} pid;

/**
 * Used for motor setup
 *
 * @param 	iPort         The motor being setup
 * @param 	biIsReversed  Finds out if the motor is reversed
 * @param   bIsTruespeed  Finds out if the motor uses truespeed
 *
 * @return	Motor setup complete+
 */
void setupMotor(unsigned char eMotor, bool bIsReversed, bool bIsTruespeed);

/**
 * Sets the motor speed based on the configuration
 *
 * @param 	iPort  The motor being set
 * @param 	iSpeed The motor speed being set
 *
 * @return	Motor set to desired speed
 */
void setMotor(unsigned char eMotor, int iSpeed);

/**
 * Sets the motor speed to the left / right side of chassis
 *
 * @param 	iSpeedL  Sets left side of chassis
 * @param 	iSpeedR  Sets right side of chassis
 *
 * @return	Motor speed to each chassis motor
 */
void tank(int iSpeedL, int iSpeedR);

/**
 * Sets the motor speed to mogo lift
 *
 * @param 	iSpeed  Sets mogo lift speed
 *
 * @return	Motor speed to each mogo lift motor
 */
void mogo(int iSpeed);

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */
void arm(int iSpeed);

/**
 * PID for Arm
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
int iArmPID(int iDes);

/**
 * Checks if arm is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if arm is at position, else false
 */
bool armIsAtPos(int iDes);

/**
 * PID for Mogo
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
int iMogoPID(int iDes);

/**
 * Checks if mogo is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if mogo is at position, else false
 */
bool mogoIsAtPos(int iDes);

/**
 * PID for right chassis
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
int iRightChassisPID(int iDes);

/**
 * Checks if right chassis is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if right chassis is at position, else false
 */
bool rCIsAtPos(int iDes);

/**
 * PID for left chassis
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
int iLeftChassisPID(int iDes);

/**
 * Checks if left chassis is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if left chassis is at position, else false
 */
bool lCIsAtPos(int iDes);

/* end of header guard */
#endif
