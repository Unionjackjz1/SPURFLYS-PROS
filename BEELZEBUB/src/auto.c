// Include function prototypes
#include "main.h"

void
auton(int iLeftChassisDesSpeed,  int iLeftChassisDesPos,
  int iRightChassisDesSpeed, int iRightChassisDesPos,
  int iArmDesSpeed,          int iArmDesPos,
  int iMogoDesSpeed,         int iMogoDesPos, bool bClaw) {

  while(!(lCIsAtPos(iLeftChassisDesPos) && rCIsAtPos(iLeftChassisDesPos) && armIsAtPos(iArmDesPos) && mogoIsAtPos(iMogoDesPos))) {
    tank(clipNum(iLeftChassisPID(iLeftChassisDesPos), iLeftChassisDesSpeed), clipNum(iRightChassisPID(iRightChassisDesPos), iRightChassisDesSpeed));
    arm(clipNum(iArmPID(iArmDesPos), iArmDesSpeed));
    mogo(clipNum(iMogoPID(iMogoDesPos), iMogoDesSpeed));
    digitalWrite(12, bClaw);
  }
}

void
statGoal( ) {
  imeReset(LEFT_CHASSIS_IME);
  imeReset(RIGHT_CHASSIS_IME);

  auton(100, 650, 100, 650, 127, 1200, 127, -4000, true);
  delay(500);
  auton(100, 650, 100, 650, 127, 1000, 127, 0, true);
  auton(100, 650, 100, 650, 127, 1000, 127, 0, false);
  delay(250);
  auton(100, 400, 100, 400, 127, 1000, 127, 0, false);
}

void
rPush( ) {
  imeReset(LEFT_CHASSIS_IME);
  imeReset(RIGHT_CHASSIS_IME);

}

void
lPush( ) {
  imeReset(LEFT_CHASSIS_IME);
  imeReset(RIGHT_CHASSIS_IME);

}

void
rPushScore( ) {
  imeReset(LEFT_CHASSIS_IME);
  imeReset(RIGHT_CHASSIS_IME);

}

void
lPushScore( ) {
  imeReset(LEFT_CHASSIS_IME);
  imeReset(RIGHT_CHASSIS_IME);

}

/**
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode.
 If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void
autonomous( ) {
  lcdClear(uart2);
  lcdSetText(uart2, 1, "Running");
  lcdSetText(uart2, 2, rgC[iAuton-1]);

  switch(iAuton) {
    case 1: statGoal();   break;
    case 2: rPush();      break;
    case 3: lPush();      break;
    case 4: rPushScore(); break;
    case 5: lPushScore(); break;
  }
}
