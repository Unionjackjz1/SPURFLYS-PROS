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
void
armControl( bool bBtnUp, bool bBtnDown ) {
	static int iDes, iOutput;
	static float kP = 0.1;
	if(bBtnUp || bBtnDown) {
		iOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
		iDes = getArmSensor();
	}
	else {
		iOutput = (iDes - getArmSensor()) * kP;
	}
	arm(iOutput);
}

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
void
mogoIntakeControl( bool bBtnUp, bool bBtnDown, bool bSlow, bool bBrake ) {
	static int iOutput;
	static bool bIsBraking;
	if(bBrake) {
		bIsBraking = true;
	}

	if(bBtnUp || bBtnDown) {
		bIsBraking = false;
		if(bSlow) {
			iOutput = bBtnUp ? -80 : 80;
		}else{
			iOutput = bBtnUp ? -127 : 127;
		}
	}
	else if(bIsBraking) {
		iOutput = iMogoPID(0);
	}
	else {
		iOutput = 0;
	}
	mogo(iOutput);
}
