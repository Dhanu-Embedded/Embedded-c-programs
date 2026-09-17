// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
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

#define cs1 RB3
#define cs2 RB4
void main(void)
{
    TRISB0 = 1;     
    TRISB1 = 0;     

    TRISD0 = 1;     
    TRISD1 = 0;     

    TRISB3 = 0;     
    TRISB4 = 0;     

    TRISC3 = 0;     
    TRISC4 = 1;     
    TRISC5 = 0;     

    SSPCON = 0B00100000;
    SSPSTAT = 0X00;

    cs1 = 1;
    cs2 = 1;
    RB1 = 0;
    RD1 = 0;
    while(1)
    {
        
        if(RB0 == 1)
        {
            RB1 = 1;

            cs1 = 0;
            SSPBUF = 0x06;          
            while(SSPIF == 0);
            SSPIF = 0;
            cs1 = 1;

            cs1 = 0;
            SSPBUF = 0x02;          
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;          
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 'A';          
            while(SSPIF == 0);
            SSPIF = 0;

            cs1 = 1;
            __delay_ms(10);

            while(RB0 == 1);       

            RB1 = 0;

           
            cs1 = 0;
            SSPBUF = 0x06;
            while(SSPIF == 0);
            SSPIF = 0;
            cs1 = 1;

            cs1 = 0;
            SSPBUF = 0x02;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0xFF;
            while(SSPIF == 0);
            SSPIF = 0;

            cs1 = 1;
            __delay_ms(10);
        }
        if(RD0 == 1)
        {
            RD1 = 1;

            cs2 = 0;
            SSPBUF = 0x06;
            while(SSPIF == 0);
            SSPIF = 0;
            cs2 = 1;

            cs2 = 0;
            SSPBUF = 0x02;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 'B';
            while(SSPIF == 0);
            SSPIF = 0;

            cs2 = 1;
            __delay_ms(10);

            while(RD0 == 1);        
            RD1 = 0;

            cs2 = 0;
            SSPBUF = 0x06;
            while(SSPIF == 0);
            SSPIF = 0;
            cs2 = 1;

            cs2 = 0;
            SSPBUF = 0x02;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0x00;
            while(SSPIF == 0);
            SSPIF = 0;

            SSPBUF = 0xFF;
            while(SSPIF == 0);
            SSPIF = 0;

            cs2 = 1;
            __delay_ms(10);
        }
    }
}