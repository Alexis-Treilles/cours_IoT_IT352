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

InterruptIn sw(BUTTON1);

Ticker flipper;
float freq_count = 5;
char flag = 0;

void incr_count()
{
    flag = 1;
    if(freq_count <= 0.5)
        freq_count = 5;
    else
        freq_count -= 0.5;
}

void flip()
{
    led = !led;
}

int main()
{
    sw.rise(&incr_count);

    printf("begin\n\r");

    flipper.attach(&flip, freq_count);

    while (1) {
        if(flag)
        {
            printf("freq: %d*e-1 s\n\r", (int)(freq_count*10.0)); //ne prend pas en charge %f donc ecriture scientifique.
            flag = 0;
            flipper.attach(&flip, freq_count);
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

/*
output:
begin
freq: 40*e-1 s
freq: 35*e-1 s
freq: 30*e-1 s
freq: 25*e-1 s
freq: 20*e-1 s
freq: 10*e-1 s
freq: 5*e-1 s
freq: 50*e-1 s
*/