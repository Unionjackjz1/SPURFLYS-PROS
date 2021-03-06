// Include function prototypes
#include "main.h"

/**
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void
initializeIO( ) {
  setupMotor(ARM_R1,    true,  false);
  setupMotor(ARM_R2,    true,  false);
  setupMotor(ARM_L1,    false, false);
  setupMotor(ARM_L2,    false, false);
  setupMotor(MOGO_L,    true,  false);
  setupMotor(CHASSIS_L, false, true);
  setupMotor(MOGO_R,    false, false);
  setupMotor(CHASSIS_R, true,  true);
}

/**
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void
initialize( ) {
  pinMode(12, OUTPUT);

  analogCalibrate(1);
  analogCalibrate(2);
  analogCalibrate(3);

  lcdInit(uart2);
  lcdClear(uart2);
  lcdSetBacklight(uart2, true);

  int IMECount = imeInitializeAll();
  if(IMECount != NUMBER_OF_IME) {
    lcdPrint(uart2, 1, "IME IZ DED");
  }
}
