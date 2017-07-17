// Include function prototypes
#include "main.h"

void
initializeIO( ) {
  setupMotor(CHASSIS_L1, false, true);
  setupMotor(CHASSIS_L2, true,  true);
  setupMotor(CHASSIS_L3, true,  true);
  setupMotor(ARM_L,      false, false);
  setupMotor(ARM_R,      false, false);
  setupMotor(CHASSIS_R3, false, true);
  setupMotor(CHASSIS_R2, false, true);
  setupMotor(CHASSIS_R1, true,  true);
}

void
initialize( ) {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(ARM_SENSOR_TOP, INPUT);
  pinMode(ARM_SENSOR_BOTTOM, INPUT);

  ARM_SENSOR = encoderInit(ARM_SENSOR_TOP, ARM_SENSOR_BOTTOM, true);
  encoderReset(ARM_SENSOR);
}
