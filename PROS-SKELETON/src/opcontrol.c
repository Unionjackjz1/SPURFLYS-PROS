#include "main.h"
#include "motor.h"

int iArmDes, iOutput;
void
armControl( bool bBtnUp, bool bBtnDown ) {
	if(bBtnUp || bBtnDown) {
		iOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
		iArmDes = analogReadCalibrated(ARM_SENSOR);
	}
	else {
		iOutput = iArmPID( iArmDes );
	}
	arm(iOutput);
}

void
coneIntakeControl( ) {
	if(joystickGetDigital(1, 5, JOY_UP)) {
		digitalWrite(12, !(digitalRead(12)));
		while(joystickGetDigital(1, 5, JOY_UP)){}
	}
}

void
mogoIntakeControl( ) {
	if(joystickGetDigital(1, 5, JOY_DOWN)) {
		digitalWrite(11, !(digitalRead(11)));
		while(joystickGetDigital(1, 5, JOY_DOWN)){}
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
