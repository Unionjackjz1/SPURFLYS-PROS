// Include function prototypes
#include "main.h"

/**
 * Intake Control
 *
 * @return Togglable pneumatics
 */
void
coneIntakeControl( ) {
	if(joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
		digitalWrite(12, !(digitalRead(12)));
		while(joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)){
			delay(20); //Don't hog the CPU!
		}
	}
}

/**
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void
operatorControl( ) {
	//Create task handler to allow for multitasking
	TaskHandle coneTaskHandle = taskRunLoop(coneIntakeControl, 50);
	while( isEnabled() ) {
		/**
		 * Chassis Control (tank)
		 *
		 * @param  iSpeedL  Speed for left chassis
		 * @param  iSpeedR  Speed for right chassis
		 *
		 * @return iSpeedL and iSpeedR to their respective sides of the chassis
		 */
		tank(joystickGetAnalog(MAIN_JOYSTICK, 3), joystickGetAnalog(MAIN_JOYSTICK, 2));
		/**
		 * Arm Control
		 *
		 * @param  bBtnUp    Boolean for button up
		 * @param  bBtnDown  Boolean for button down
		 *
		 * @return \
		 * if no button is pressed, run a PID loop to stay at last
		 * position. If button is pressed, go up / down respectively.
		 */
		armControl(joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP), joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN));
		/**
		 * Mobile Goal Intake Control
		 *
		 * @param  bBtnUp    Boolean for button up
		 * @param  bBtnDown  Boolean for button down
		 *
		 * @return \
		 * if no button is pressed, do nothing. if bBrake,
		 * set mogo lift to closed. if bBtnUp/bBtnDown, go
		 * up/down respectively
		 */
		mogoIntakeControl(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_UP), joystickGetDigital(MAIN_JOYSTICK, 5, JOY_DOWN), joystickGetDigital(MAIN_JOYSTICK, 7, JOY_DOWN));

		delay(20); //Don't hog the CPU!
	}
	//Delete the multitasking handler once it is not being used
	taskDelete(coneTaskHandle);
}
