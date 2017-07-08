/**
 * ALL DESCRIPTIONS OF FUNCTIONS ARE IN MOTOR.C
 */

#ifndef MOTOT_H_
#define MOTOR_H_

#include "main.h"

#define ARM_L      1
#define CHASSIS_L1 2
#define CHASSIS_L2 3
#define CHASSIS_L3 4
#define CHASSIS_L4 5
#define CHASSIS_R4 6
#define CHASSIS_R3 7
#define CHASSIS_R2 8
#define CHASSIS_R1 9
#define ARM_R      10

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
