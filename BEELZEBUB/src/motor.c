// Include function prototypes
#include "main.h"

/**
 * Ports 1 and 10 linear rpm remapped values
 */
 int L298[128] = {
 	0, 0, 0, 0, 0, 0, 0, 0,
 	0, 0, 0, 0, 0, 0, 0, 11, 11, 12,
 	12, 12, 12, 13, 13, 13, 14, 14, 14, 14,
 	15, 15, 15, 16, 16, 16, 17, 17, 17, 18,
 	18, 18, 19, 19, 19, 20, 20, 20, 21, 21,
 	22, 22, 23, 23, 23, 24, 25, 25, 26, 26,
 	26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
 	31, 32, 32, 33, 33, 34, 35, 35, 35, 35,
 	35, 35, 38, 38, 39, 41, 41, 41, 42, 43,
 	45, 46, 47, 47, 48, 49, 49, 50, 51, 52,
 	53, 54, 55, 56, 58, 59, 63, 66, 67, 70,
 	73, 74, 75, 78, 80, 84, 87, 88, 92, 95,
 	97, 100, 105, 108, 114, 117, 121, 122, 124, 127
 };

/**
 * Port 2-9 linear rpm remapped values
 */
int MC29[ 128 ] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 13, 13, 14,
	14, 14, 14, 15, 15, 15, 15, 16, 16, 16,
	16, 16, 17, 17, 17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 20, 20, 20, 20, 21, 21, 21, 22,
	22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
	25, 25, 25, 26, 26, 26, 27, 27, 27, 28,
	28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
	32, 33, 33, 34, 34, 35, 36, 36, 37, 37,
	38, 39, 40, 40, 41, 42, 43, 44, 45, 46,
	46, 48, 49, 50, 51, 53, 55, 56, 58, 60,
	62, 64, 67, 70, 72, 76, 79, 83, 84, 127,
};

/**
 * Sensor value for arm
 *
 * @return	Currenst sensor value
 */
int getArmSensor( ) {
  return (analogReadCalibrated(1)+(-analogReadCalibrated(2)))/2;
}

/**
 * Sensor value for mogo lift
 *
 * @return	Current sensor value
 */
int getMogoSensor( ) {
  return (analogReadCalibrated(3));
}

/**
 * Sensor value for right chassis
 *
 * @return	Current sensor value
 */
int getRightChassisSensor( ) {
  int counts;
  imeGet(RIGHT_CHASSIS_IME, &counts);
  return -counts;
}

/**
 * Sensor value for left chassis
 *
 * @return	Current sensor value
 */
int getLeftChassisSensor( ){
  int counts;
  imeGet(LEFT_CHASSIS_IME, &counts);
  return counts;
}

/**
 * struct definition for motor setup
 */
enMotor port[10];

/**
 * Used for motor setup
 *
 * @param 	iPort         The motor being setup
 * @param 	biIsReversed  Finds out if the motor is reversed
 * @param   bIsTruespeed  Finds out if the motor uses truespeed
 *
 * @return	Motor setup complete+
 */
void
setupMotor( unsigned char iPort, bool bIsReversed, bool bIsTruespeed ) {
  port[iPort-1].bReverse   = bIsReversed;
  port[iPort-1].bTruespeed = bIsTruespeed;
}

/**
 * Sets the motor speed based on the configuration
 *
 * @param 	iPort  The motor being set
 * @param 	iSpeed The motor speed being set
 *
 * @return	Motor set to desired speed
 */
void
setMotor( unsigned char iPort, int iSpeed ) {
  iSpeed = port[iPort-1].bReverse == true ? -iSpeed : iSpeed;

  if(port[iPort-1].bTruespeed == true) {
    if(iPort == 1 || iPort == 10) {
      iSpeed = sgn(iSpeed) * L298[abs(clipNum(iSpeed, 127))];
    }
    else {
      iSpeed = sgn(iSpeed) * MC29[abs(clipNum(iSpeed, 127))];
    }
  }
  motorSet( iPort , iSpeed );
}

/**
 * Sets the motor speed to the left / right side of chassis
 *
 * @param 	iSpeedL  Sets left side of chassis
 * @param 	iSpeedR  Sets right side of chassis
 *
 * @return	Motor speed to each chassis motor
 */
void
tank( int iSpeedL, int iSpeedR ) {
  setMotor(CHASSIS_L, iSpeedL);
  setMotor(CHASSIS_R, iSpeedR);
}

/**
 * Sets the motor speed to mogo lift
 *
 * @param 	iSpeed  Sets mogo lift speed
 *
 * @return	Motor speed to each mogo lift motor
 */
void
mogo( int iSpeed ) {
  setMotor(MOGO_L, iSpeed);
  setMotor(MOGO_R, iSpeed);
}

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */
void
arm( int iSpeed ) {
  setMotor(ARM_L1, iSpeed);
  setMotor(ARM_L2, iSpeed);
  setMotor(ARM_R2, iSpeed);
  setMotor(ARM_R1, iSpeed);
}

/**
 * HOW TO TUNE PID:
 * 1. Set all gains to zero.
 * 2. Increase the P gain until the response to a disturbance is steady oscillation.
 * 3. Increase the D gain until the the oscillations go away (i.e. it's critically damped).
 * 4. Repeat steps 2 and 3 until increasing the D gain does not stop the oscillations.
 * 5. Set P and D to the last stable values.
 */

/**
 * PID for Arm
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
pid sArmPID;
int
iArmPID( int iDes ) {
  sArmPID.derivative = sArmPID.error - sArmPID.lastError;
	sArmPID.kP         = 0.4;
  sArmPID.kD         = 8;
	sArmPID.current    = getArmSensor();
	sArmPID.error      = iDes - sArmPID.current;
  sArmPID.lastError  = sArmPID.error;
	return ( (sArmPID.error * sArmPID.kP) + (sArmPID.derivative * sArmPID.kD) );
}

/**
 * Checks if arm is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if arm is at position, else false
 */
bool
armIsAtPos( int iDes ) {
  return abs(iDes - getArmSensor()) < 20 ? true : false;
}

/**
 * PID for Mogo
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
pid sMogoPID;
int
iMogoPID( int iDes ) {
  sMogoPID.derivative = sMogoPID.error - sMogoPID.lastError;
	sMogoPID.kP         = .25;
  sMogoPID.kD         = 5;
	sMogoPID.current    = getMogoSensor();
	sMogoPID.error      = iDes - sMogoPID.current;
  sMogoPID.lastError  = sMogoPID.error;
	return ( (sMogoPID.error * sMogoPID.kP) + (sMogoPID.derivative * sMogoPID.kD) );
}

/**
 * Checks if mogo is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if mogo is at position, else false
 */
bool
mogoIsAtPos( int iDes ) {
  return abs(iDes - getMogoSensor()) < 40 ? true : false;
}

/**
 * PID for Right Chassis
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
pid sRCPID;
int
iRightChassisPID( int iDes ) {
  sRCPID.derivative = sRCPID.error - sRCPID.lastError;
	sRCPID.kP         = 2;
  sRCPID.kD         = 1;
	sRCPID.current    = getRightChassisSensor();
	sRCPID.error      = iDes - sRCPID.current;
  sRCPID.lastError  = sRCPID.error;
	return ( (sRCPID.error * sRCPID.kP) + (sRCPID.derivative * sRCPID.kD) );
}

/**
 * Checks if righ chassis tis at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if right chassis is at position, else false
 */
bool
rCIsAtPos( int iDes ) {
  return abs(iDes - getRightChassisSensor()) < 10 ? true : false;
}

/**
 * PID for Left Chassis
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
pid sLCPID;
int
iLeftChassisPID( int iDes ) {
  sLCPID.derivative = sLCPID.error - sLCPID.lastError;
	sLCPID.kP         = 2;
  sLCPID.kD         = 1;
	sLCPID.current    = getLeftChassisSensor();
	sLCPID.error      = iDes - sLCPID.current;
  sLCPID.lastError  = sLCPID.error;
	return ( (sLCPID.error * sLCPID.kP) + (sLCPID.derivative * sLCPID.kD) );
}

/**
 * Checks if left chassis is at desired value
 *
 * @param 	iDes  Desired value to check
 *
 * @return	True if left chassis is at position, else false
 */
bool
lCIsAtPos( int iDes ) {
  return abs(iDes - getLeftChassisSensor()) < 10 ? true : false;
}
