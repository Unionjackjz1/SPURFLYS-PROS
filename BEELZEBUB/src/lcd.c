// Include function prototypes
#include "main.h"

void
waitForRelease(){
  while(lcdReadButtons(uart2)!=0){
    delay(20); //Don't hog the CPU!
  }
}

void
autonSelector( ) {
  static bool bLcd = false;
  if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP)) {
    while(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP)){
      delay(20); //Don't hog the CPU!
    }
    bLcd = !bLcd;
  }
  kMaxPage = 5;
  kMinPage = 1;
  iAuton = kMinPage;
  char rgC[5][16] = {"Stat Goal", "R Push", "L Push", "R Push Score", "L Push Score"};

  if(!bLcd) {
    lcdSetText(uart2, 1, "Beelzebub");
    lcdSetText(uart2, 2, "User Control");
    delay(50);
    lcdClear(uart2);
  }

  if(bLcd) {
    if(lcdReadButtons(uart2) == 1) {
      iAuton = iAuton == kMinPage ? kMaxPage : iAuton-1;
      waitForRelease();
    }
    else if(lcdReadButtons(uart2) == 4) {
      iAuton = iAuton == kMaxPage ? kMinPage : iAuton+1;
      waitForRelease();
    }
    else if(lcdReadButtons(uart2) == 2) {
      bLcd = false;
      waitForRelease();
    }

    lcdSetText(uart2, 1, "Auton Select");
    lcdSetText(uart2, 2, rgC[iAuton-1]);
    delay(50);
    lcdClear(uart2);
  }
}
