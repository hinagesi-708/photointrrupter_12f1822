
/* 
 * File:   slave_for_photointrrupter_12f1822.c
 * Author: kayoko
 *
 * Created on 2015/08/03, 10:14
 */

/********************************************
 *  compiler    MPLAB XC8(v1.34)            *
 *  PIC         PIC12F1822                  *
 *  clock        16MHz(INTIO)               *
 *                                          *
 *  use_port                                *
 *                __________                *
 *          Vdd---|1  ●   8|---Vss         *
 * (RA5)Ptint_2---|2       7|---Ptint_1(RA0)*
 *      (RA4)×---|3       6|---SCL(RA1)    *
 *      (RA3)×---|4       5|---SDA(RA2)    *
 *                ==========                *
 ********************************************/
#include <xc.h>
#include "I2C_slave.h"

#pragma config CLKOUTEN = OFF
#pragma config WDTE     = OFF
#pragma config PWRTE    = ON
#pragma config CP       = OFF
#pragma config BOREN    = ON
#pragma config FCMEN    = OFF
#pragma config MCLRE    = ON
#pragma config CPD      = OFF
#pragma config IESO     = OFF
#pragma config FOSC     = INTOSC

#pragma config LVP      = ON

#define _XTAL_FREQ 16000000


void init();
unsigned long count_time = 0;

int main(void) {
    init();
    I2C_init();

    while (1) {
        if(RA0 == 0){
            count_time = 0;
            while(RA5 == 1){
                __delay_us(1);
                count_time++;
                if(count_time > 3000000000) break;
            }
        }
        send_data[0] = count_time % 0x100;
        send_data[1] = count_time / 0x100;
        send_data[2] = count_time / 0x10000;
        send_data[3] = count_time / 0x1000000;
    }

    return (0);
}

void init() {
    OSCCONbits.IRCF = 0b1111;       //Set oscillator 16MHz
    ANSELA  = 0x00;                 //Set RA pins digital
    TRISA0 = 1;
    TRISA5 = 1;

    PORTA = 0x00;                   //Set PORTA Low
    return;
}

static void interrupt forinterrupt(){
    #include "I2C_slave_int.h"
}
