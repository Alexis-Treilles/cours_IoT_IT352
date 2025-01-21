/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

InterruptIn sw(BUTTON1);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

void flip()
{
    led = !led;
}

int main()
{
    sw.rise(&flip);

    printf("begin\n");

    while (true) {
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
