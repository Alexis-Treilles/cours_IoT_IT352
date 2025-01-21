/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    DigitalIn sw(BUTTON1);

    // check mypin object is initialized and connected to a pin
    if (sw.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }

    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    sw.mode(PullUp);

    printf("begin\n");

    while (true) {
        printf("mypin has value : %d \n\r", sw.read());
        led = sw.read();
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
