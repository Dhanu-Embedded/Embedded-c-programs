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
void start()
{
    SEN = 1;
    while(SSPIF == 0);
    SSPIF = 0;
}
void stop()
{
    PEN = 1;
    while(SSPIF == 0);
    SSPIF = 0;
}
void data(char d)
{
    SSPBUF = d;
    while(SSPIF == 0);
    SSPIF = 0;
}
char read_data()
{
    RCEN = 1;
    while(SSPIF == 0);
    SSPIF = 0;
    return SSPBUF;
}
void display(char count)
{
    start();
    data(0x42);

    if(count == 0)
        data(0x3F);
    else if(count == 1)
        data(0x06);
    else if(count == 2)
        data(0x5B);
    else if(count == 3)
        data(0x4F);
    else if(count == 4)
        data(0x66);
    else if(count == 5)
        data(0x6D);
    else if(count == 6)
        data(0x7D);
    else if(count == 7)
        data(0x07);
    else if(count == 8)
        data(0x7F);
    else if(count == 9)
        data(0x6F);
    stop();
}
void main(void)
{
    char button;
    int count;

    SSPCON = 0B00101000;
    SSPADD = 0x19;
    start();
    data(0x40);
    data(0x00);
    stop();

    start();
    data(0x42);
    data(0x00);
    stop();

    while(1)
    {
        
        start();
        data(0x41);
        button = read_data();
        stop();

        if(button == 1)
        {
            for(count = 0; count <= 9; count++)
            {
                start();
                data(0x41);
                button = read_data();
                stop();

                if(button == 0)
                    break;
                display(count);
                __delay_ms(1000);
            }
        }
        else
        {
            for(count = 9; count >= 0; count--)
            {
               
                start();
                data(0x41);
                button = read_data();
                stop();
                if(button == 1)
                    break;
                display(count);
                __delay_ms(1000);
            }
        }
    }
}

