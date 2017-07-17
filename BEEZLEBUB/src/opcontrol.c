// Include function prototypes
#include "main.h"

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
int iArmDes = 75, iOutput;
void
armControl( bool bBtnUp, bool bBtnDown ) {
	if(bBtnUp || bBtnDown) {
		iOutput = bBtnUp ? 127 : (bBtnDown ? -80 : 0);
		iArmDes = encoderGet(ARM_SENSOR);
	}
	else {
		iOutput = iArmPID( iArmDes );
	}
	arm(iOutput);
}


/**
 * Intake Control
 *
 * @return Toggle for each system
 */
void
coneIntakeControl( ) {
	if(joystickGetDigital(1, 5, JOY_UP)) {
		digitalWrite(10, !(digitalRead(10)));
		while(joystickGetDigital(1, 5, JOY_UP)){delay(20);}
	}
}

void
mogoIntakeControl( ) {
	if(joystickGetDigital(1, 5, JOY_DOWN)) {
		digitalWrite(12, !(digitalRead(12)));
		digitalWrite(11, !(digitalRead(11)));
		while(joystickGetDigital(1, 5, JOY_DOWN)){delay(20);}
	}
}

void
operatorControl( ) {
	TaskHandle coneTaskHandle = taskRunLoop(coneIntakeControl, 50);
	TaskHandle mogoTaskHandle = taskRunLoop(mogoIntakeControl, 50);
	while( isEnabled() ) {
		tank( joystickGetAnalog(1, 3), joystickGetAnalog(1, 2) );
		armControl( joystickGetDigital(1, 6, JOY_UP), joystickGetDigital(1, 6, JOY_DOWN) );

		delay(20);
	}
	taskDelete(coneTaskHandle);
	taskDelete(mogoTaskHandle);
}
