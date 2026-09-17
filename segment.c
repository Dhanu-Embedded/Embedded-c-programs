// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 20000000
#define A  RB0
#define B  RB1
#define C  RB2
#define D  RB3
#define C1 RD0
#define C2 RD1
#define C3 RD2
#define C4 RD3
#define SEG PORTC
void main(void)
{
    TRISB = 0x00;
    TRISD = 0xFF;
    TRISC = 0x00;
    SEG = 0x00;
    while(1)
    {
        
        A = 0;
        B = 0;
        C = 1;
        D = 0;
        if(C1 == 1)
        {
            SEG = 0x06;       
            while(C1 == 1);
        }
        else if(C2 == 1)
        {
            SEG = 0x5B;       
            while(C2 == 1);
        }
        else if(C3 == 1)
        {
            SEG = 0x4F;       
            while(C3 == 1);
        }
        A = 0;
        B = 1;
        C = 0;
        D = 0;
        if(C1 == 1)
        {
            SEG = 0x66;    
            while(C1 == 1);
        }
        else if(C2 == 1)
        {
            SEG = 0x6D;       
            while(C2 == 1);
        }
        else if(C3 == 1)
        {
            SEG = 0x7D;       
            while(C3 == 1);
        }
        A = 1;
        B = 0;
        C = 0;
        D = 0;

        if(C1 == 1)
        {
            SEG = 0x07;       
            while(C1 == 1);
        }
        else if(C2 == 1)
        {
            SEG = 0x7F;       
            while(C2 == 1);
        }
        else if(C3 == 1)
        {
            SEG = 0x6F;       
            while(C3 == 1);
        }
        A = 0;
        B = 0;
        C = 0;
        D = 1;
        if(C2 == 1)
        {
            SEG = 0x3F;       
            while(C2 == 1);
        }
    }
}