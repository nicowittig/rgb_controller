//
// Created by Nico Wittig on 2018-12-14.
//

#ifndef CONTROLLER_NW_TOOLKIT_H
#define CONTROLLER_NW_TOOLKIT_H

#define DELAY(delay) (delay_counter % ((int) ((delay) / delay_balance)) == 0 && delay_counter >= ((delay) / delay_balance))

int modulo(int a, int b);
int freeRam();

#endif //CONTROLLER_NW_TOOLKIT_H
