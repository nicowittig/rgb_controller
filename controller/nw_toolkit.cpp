//
// Created by Nico Wittig on 2019-01-12.
//

#include "nw_toolkit.h"

int modulo(int a, int b) { return (a < 0) ? b+(a%b) : a%b; }

int freeRam() {
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void softReset() {
    asm volatile ("  jmp 0");
}
