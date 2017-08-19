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
int iArmDes, iArmOutput;
void
armControl( bool bBtnUp, bool bBtnDown ) {
	if(bBtnUp || bBtnDown) {
		iArmOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
		iArmDes = getArmSensor();
	}
	else {
		iArmOutput = iArmPID(iArmDes);
	}
	arm(iArmOutput);
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
int iMogoOutput;
void
mogoIntakeControl( bool bBtnUp, bool bBtnDown, bool bBrake ) {
	if(bBtnUp || bBtnDown) {
		iMogoOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
	}
	else if(bBrake) {
		iMogoOutput = iMogoPID(0);
	}
	mogo(iMogoOutput);
}
