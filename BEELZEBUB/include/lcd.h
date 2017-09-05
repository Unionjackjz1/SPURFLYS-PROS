/* header guard */
#ifndef LCD_H_
#define LCD_H_

int kMaxPage = 5;
int kMinPage = 1;
int iAuton = kMinPage;
char rgC[5][16] = {"Stat Goal", "R Push", "L Push", "R Push Score", "L Push Score"};

void autonSelector();
void waitForRelease();


#endif
