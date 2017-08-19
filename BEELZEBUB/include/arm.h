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
void armControl(bool bBtnUp, bool bBtnDown);

/**
 * Mobile Goal Intake Control
 *
 * @param  bBtnUp    Boolean for button up
 * @param  bBtnDown  Boolean for button down
 *
 * @return \
 * if no button is pressed, set 0 motor power. else,
 * go up/down respectively
 */
void mogoIntakeControl(bool bBtnUp, bool bBtnDown, bool bBrake);
