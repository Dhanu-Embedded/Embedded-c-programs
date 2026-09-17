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
#include <pic16f877a.h>
#define _XTAL_FREQ 20000000
#define LED RB0
void main(void) {
    TRISBbits.TRISB0=0;
    LED=0;
    T1CON=0B00110001;
    TMR1H=0xE7;
    TMR1L=0x96;
    PIR1bits.TMR1IF=0;
    PIE1bits.TMR1IE=1;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    while(1)
    {
        
    }
  
}
void __interrupt() timer(void)
{
    if(PIR1bits.TMR1IF==1)
    {
        LED=~LED;
        TMR1H=0xE7;
        TMR1L=0x96;
        PIR1bits.TMR1IF=0;
    }
}
