#ifndef _FUNCTION_H_
#define _FUNCTION_H_

void gotoXY(int x, int y);
void setCursorVisible(bool state);
void fixConsoleSize();
int random(int start, int end); // return a random integer in range [start, end)
//void flushInputStart();
//void flushInputEnd();

#endif