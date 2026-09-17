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
void lcd_cmd(unsigned char cmd)
{
    PORTD = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}
void lcd_data(unsigned char data)
{
    PORTD = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}
void lcd_init(void)
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);
}
void main(void)
{
    unsigned int adc;
    unsigned char hundreds, tens, ones;
    TRISA = 0x01;
    TRISB = 0x00;
    TRISD = 0x00;

    ADCON0 = 0x41;
    ADCON1 = 0x8E;

    lcd_init();
    while(1)
    {
        GO_nDONE = 1;
        while(GO_nDONE);
        adc = ((unsigned int)ADRESH << 8) | ADRESL;
        hundreds = adc / 100;
        tens = (adc / 10) % 10;
        ones = adc % 10;
        lcd_cmd(0x80);
        lcd_data('A');
        lcd_data('D');       //lcd display//
        lcd_data('C');
        lcd_data('=');

        lcd_data(hundreds + '0');
        lcd_data(tens + '0');       
        lcd_data(ones + '0');
        EEADR = 0x50;
        EEDATA = hundreds + '0';
        EEPGD = 0;
        WREN = 1;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        WR = 1;
        while(WR);
        WREN = 0;
        
        EEADR = 0x51;
        EEDATA = tens + '0';
        EEPGD = 0;
        WREN = 1;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        WR = 1;
        while(WR);
        
        WREN = 0;
        EEADR = 0x52;
        EEDATA = ones + '0';
        EEPGD = 0;
        WREN = 1;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        WR = 1;
        while(WR);
        WREN = 0;
        __delay_ms(500);
    }
}
