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

#define rs RB0
#define rw RB1
#define en RB2
#define rs485 RC5
void lcd_cmd(unsigned char cmd)
{
    rs = 0;
    rw = 0;
    PORTD = cmd;
    en = 1;
    __delay_us(40);
    en = 0;
}
void lcd_data(unsigned char data)
{
    rs = 1;
    rw = 0;
    PORTD = data;
    en = 1;
    __delay_us(40);
    en = 0;
}
void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}
void lcd_init(void)
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    __delay_ms(2);
    lcd_cmd(0x06);
}
void main(void)
{
    unsigned char data;
    unsigned char i;

    TRISB = 0x00;
    TRISD = 0x00;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC5 = 0;

    TXSTA = 0B00100110;
    RCSTA = 0B10010000;
    SPBRG = 129;

    rs485 = 0;

    lcd_init();

    lcd_cmd(0x80);
    lcd_string("ADC VALUE:");
    while(1)
    {
        while(RCIF == 0);        //data vara varaikum wait panum
        if(RCREG == 0xFF)
        {
            lcd_cmd(0x8A);
            for(i = 0; i < 4; i++)
            {
                while(RCIF == 0);
                data = RCREG;
                lcd_data(data);
            }
        }
    }
}