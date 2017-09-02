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
  const int kMaxPage = 5;
  const int kMinPage = 1;
  static int iAuton = kMinPage;
  bool bLcd = true;
  char rgC[5][16] = {"Stat Goal", "R Push", "L Push", "R Push Score", "L Push Score"};

  while(bLcd) {
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
