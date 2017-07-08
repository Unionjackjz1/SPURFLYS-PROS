#include "main.h"
#include "motor.h"

void
initializeIO( ) {
  setupMotor(ARM_L, false, false);
  setupMotor(CHASSIS_L1, false, true);
  setupMotor(CHASSIS_L2, false, true);
  setupMotor(CHASSIS_L3, false, true);
  setupMotor(CHASSIS_L4, false, true);
  setupMotor(CHASSIS_R4, true, true);
  setupMotor(CHASSIS_R3, true, true);
  setupMotor(CHASSIS_R2, true, true);
  setupMotor(CHASSIS_R1, true, true);
  setupMotor(ARM_R, true, false);
}

void
initialize( ) {
  analogCalibrate(1);
}
