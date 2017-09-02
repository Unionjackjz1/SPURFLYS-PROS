/* header guard */
#ifndef AUTO_H_
#define AUTO_H_

// Include function prototypes
#include "main.h"

void auton(int iLeftChassisDesSpeed,  int iLeftChassisDesPos,
        int iRightChassisDesSpeed, int iRightChassisDesPos,
        int iArmDesSpeed,          int iArmDesPos,
        int iMogoDesSpeed,         int iMogoDesPos, bool bClaw);

void statGoalAuton();

#endif
