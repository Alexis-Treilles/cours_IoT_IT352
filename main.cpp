/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

 /*
 Dust sensor:
    UART :
        UART1_TX (pin 69)
        UART1_RX (pin 71)

        baud rate: 9600, 
        databits: 8, 
        stopbits: 1, 
        parity: no
 
        Etape de lecture:

                |HEAD   |LEN    |CMD    |Data       |CS                           |
        --------+-------+-------+-------+-----------+--------------------------
Start : send    | 0x68  | 0x01  | 0x01  | NA        | ((65536-(HEAD+LEN+CMD+DATA))| 
        receive |               0xA5A5                                        | Reponse ok
        receive |               0x9696                                        | Reponse ko
        --------+-------+-------+-------+-----------+--------------------------
end   : send    | 0x68  | 0x01  | 0x02  | NA        | ((65536-(HEAD+LEN+CMD+DATA)) 
        receive |               0xA5A5                                        | Reponse ok
        receive |               0x9696                                        | Reponse ko
        --------+-------+-------+-------+-----------+--------------------------
read  : send    | 0x68  | 0x01  | 0x04  | NA        | ((65536-(HEAD+LEN+CMD+DATA))|
        receive | 0x40  | 0x05  | 0x04  | "DF1, DF2,| ((65536-(HEAD+LEN+CMD+DATA))| Reponse ok
                                        |  DF3, DF4 |_______________
                                        |  PM2.5 = DF1 * 256 + DF2 |
                                        |  PM10 = DF3 * 256 + DF4" |   
        receive |               0X9696                                        | Reponse ko
        
       

 */

#include "mbed.h"
#include "mbed_honeywell-hpma115/hpma115/hpma115.h"


#define wait     500ms
#define MAXIMUM_BUFFER_SIZE  32

using namespace sixtron;
using namespace std::chrono;

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

static hpma115_data_t data;

int main()
{
    HPMA115::ErrorType err;

    HPMA115 sensor(P1_UART_TX, P1_UART_RX);

    printf("\n\n------------\nHPMA115 test\n");

    err = sensor.set_adjust_coef(100);
    assert(err == HPMA115::ErrorType::Ok);

    err = sensor.start_measurement();
    assert(err == HPMA115::ErrorType::Ok);

    while (true) {
        led = !led;
        err = sensor.read_measurement(&data);
        if (err == HPMA115::ErrorType::Ok) {
            printf("Data: ");
            if (data.pm1_pm4_valid) {
                printf("PM1.0: %d, PM4.0: %d ", data.pm1_0, data.pm4_0);
            }
            printf("PM10: %d, PM2.5: %d\n", data.pm10, data.pm2_5);
        }

        ThisThread::sleep_for(wait);
    }
}