/**
 * ALL DESCRIPTIONS OF FUNCTIONS ARE IN MOTOR.C
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

#define ARM_L1     1
#define ARM_L2     2
#define ARM_L3     3
#define CHASSIS_L1 4
#define CHASSIS_L2 5
#define CHASSIS_R2 6
#define CHASSIS_R1 7
#define ARM_R3     8
#define ARM_R2     9
#define ARM_R1     10

// I setup my sensors as a part of my motor code,
// as sensors are directly linked to motors
#define ARM_SENSOR 1

typedef struct _motor{
  bool bReverse;
  bool bTruespeed;
}enMotor;

typedef struct {
	float current;
	float kP;
	float kD;
	float target;
	float error;
	float derivative;
	float lastError;
} pid;

void setupMotor(unsigned char eMotor, bool bIsReversed, bool bIsTruespeed);
void setMotor(unsigned char eMotor, int iSpeed);

void tank(int iSpeedL, int iSpeedR);
void arm(int iSpeed);

int iArmPID(int iDes);

#endif
