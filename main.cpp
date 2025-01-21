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


Timer t;
long long unsigned int count_time;
volatile char flag = 0;

void start()
{
    led = 1;
    t.start();
}

void stop()
{
    led = 0;
    t.stop();
    count_time = duration_cast<milliseconds>(t.elapsed_time()).count();
    t.reset();
    flag = 1;
}

int main()
{
    sw.rise(&start);
    sw.fall(&stop);

    printf("begin\n");

    while (true) {
        if (flag == 1)
        {
            printf("temps appuie:%llu ms\n", count_time);   
            flag = 0;
        }
                     
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

/* output:
begin
temps appuie:145 ms

*/