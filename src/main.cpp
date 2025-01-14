/***************************************************************************************
                                a v r F u n c y
                                                                Weigl қuran jan 2025
**************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"

#define TRUE                           1
#define FALSE                          0
#define HIGH                           1
#define LOW                            0
#define ON_BOARD_LED                   0x20   // PORT B:    ..x. .... 
                                                               


int main(void)
{
    int t0 = 0;
    int t1; 

    // Setup:
    
    DDRB = 0xff; 
    PORTB = ON_BOARD_LED;

    initLibraries(BAUD_RATE_115200);

    Serial.println("start!\n");
 
    // endless Loop: 

    for(;;)
    {
        t1 = millis();

        if ((t1 - t0) > 500)
        {
            PORTB ^= ON_BOARD_LED;
            t0 = t1;
        }    
    }
    
    return 0;  
}

