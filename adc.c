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
#define rs RD0

void uart_tx(unsigned char data)
{
    TXREG = data;
    while(TXIF == 0);
}
void main(void)
{
    unsigned int adc;

    TRISA0 = 1;
    TRISC6 = 0;
    TRISD0 = 0;

    ADCON0 = 0B10000001;       //ADC ON
    ADCON1 = 0B10000000;

    TXSTA = 0B00100110;        //UART TRANSMITTER SETTING
    RCSTA = 0B10000000;
    SPBRG = 129;
    while(1)
    {
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO == 1);

        adc = ((ADRESH << 8) | ADRESL);

        rs = 1;                 //RS transmitter mode

        uart_tx(0xFF);          //Special starting byte
        uart_tx((adc / 1000) + '0');
        uart_tx(((adc / 100) % 10) + '0');
        uart_tx(((adc / 10) % 10) + '0');
        uart_tx((adc % 10) + '0');

        while(TRMT == 0);
        rs = 0;                 //RECEIVER MODE

        __delay_ms(50);
    }
}