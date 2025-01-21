/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
using namespace std::chrono;

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

Ticker flipper;

void flip()
{
    led = !led;
}

int main()
{
    printf("begin\n");

    flipper.attach(&flip, 0.5);

    while (1) {

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

/* output:
begin
temps appuie:145 ms

*/