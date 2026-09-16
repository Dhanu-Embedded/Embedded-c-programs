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
void main(void)
{
    TRISD=0x00;                    //PORTD OUTPUT
    
    while(1)
    {
        PORTD=0x3F;             //0
        __delay_ms(1000);
        PORTD=0x06;             //1
        __delay_ms(1000);
        PORTD=0x5B;             //2
        __delay_ms(1000);
        PORTD=0x4F;             //3
        __delay_ms(1000);
        PORTD = 0x66;           //4
        __delay_ms(1000);
        PORTD = 0x6D;           //5
        __delay_ms(1000);
        PORTD = 0x7D;           //6
        __delay_ms(1000);
        PORTD = 0x07;           //7
        __delay_ms(1000);
        PORTD = 0x7F;           //8
        __delay_ms(1000);
        PORTD = 0x6F;           // 9
        __delay_ms(1000);
    }
    
}
