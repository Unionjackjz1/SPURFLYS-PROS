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
      iSpeed = sgn(iSpeed) * L298[abs(clipNum(iSpeed, 127, -127))];
    }
    else {
      iSpeed = sgn(iSpeed) * MC29[abs(clipNum(iSpeed, 127, -127))];
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
  setMotor(CHASSIS_L1, iSpeedL);
  setMotor(CHASSIS_L2, iSpeedL);
  setMotor(CHASSIS_L3, iSpeedL);
  setMotor(CHASSIS_R3, iSpeedR);
  setMotor(CHASSIS_R2, iSpeedR);
  setMotor(CHASSIS_R1, iSpeedR);
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
  setMotor(ARM_L, iSpeed);
  setMotor(ARM_R, iSpeed);
}


/**
 * PID for Arm
 *
 * HOW TO TUNE:
 * 1. Set all gains to zero.
 * 2. Increase the P gain until the response to a disturbance is steady oscillation.
 * 3. Increase the D gain until the the oscillations go away (i.e. it's critically damped).
 * 4. Repeat steps 2 and 3 until increasing the D gain does not stop the oscillations.
 * 5. Set P and D to the last stable values.
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */

pid sArmPID;
int
iArmPID( int iDes ) {
  sArmPID.lastError  = sArmPID.error;
	sArmPID.kP         = 3.25;
  sArmPID.kD         = 25;
	sArmPID.current    = encoderGet(ARM_SENSOR);
	sArmPID.error      = iDes - sArmPID.current;
	sArmPID.derivative = sArmPID.error - sArmPID.lastError;
	return ( (sArmPID.error * sArmPID.kP) + (sArmPID.derivative * sArmPID.kD) );
}
