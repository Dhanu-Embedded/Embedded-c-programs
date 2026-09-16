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
#define RS RB0
#define RW RB1
#define EN RB2
unsigned int adc;
void lcd_init();
void write(unsigned char data, unsigned char rs);
void main(void)
{
    TRISB = 0x00;
    TRISD = 0x00;
    ADCON0 = 0B00000001;
    ADCON1 = 0B10000000;

    lcd_init();

    ADIF = 0;
    ADIE = 1;
    PEIE = 1;
    GIE = 1;
    while(1)
    {
        GO_nDONE = 1;
        __delay_ms(10);
        write(0x80, 0);
        write(' ', 1);
        write(' ', 1);
        write(' ', 1);
        write(' ', 1);
        write(0x80, 0);
        if(adc >= 1000)
        {
            write((adc / 1000) + '0', 1);
            write(((adc / 100) % 10) + '0', 1);
            write(((adc / 10) % 10) + '0', 1);
            write((adc % 10) + '0', 1);
        }
        else if(adc >= 100)
        {
            write((adc / 100) + '0', 1);
            write(((adc / 10) % 10) + '0', 1);
            write((adc % 10) + '0', 1);
        }
        else if(adc >= 10)
        {
            write((adc / 10) + '0', 1);
            write((adc % 10) + '0', 1);
        }
        else
        {
            write(adc + '0', 1);
        }
        __delay_ms(1000);
    }
    return;
}
void __interrupt() timer(void)
{
    if(ADIF == 1)
    {
        adc = (ADRESH << 8) | ADRESL;

        ADIF = 0;
    }
}
void lcd_init()
{
    write(0x06, 0);
    write(0x0E, 0);
    write(0x1C, 0);
    write(0x80, 0);
}
void write(unsigned char data, unsigned char rs)
{
    PORTD = data;
    RS = rs;
    RW = 0;
    EN = 1;
    __delay_ms(20);
    EN = 0;
}
