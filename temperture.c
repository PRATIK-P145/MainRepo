#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 8000000  // 8MHz Oscillator

// CONFIG bits
#pragma config FOSC = HS     // High-Speed Oscillator
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF

void UART_Init(void) {
    TRISC6 = 0; // TX
    TRISC7 = 1; // RX

    SPBRG = 51;         // 9600 Baud Rate @ 8MHz
    TXSTAbits.BRGH = 1; // High Baud Rate
    RCSTAbits.SPEN = 1; // Enable Serial Port
    TXSTAbits.TXEN = 1; // Enable Transmission
    RCSTAbits.CREN = 1; // Enable Reception
}

void UART_Write(char data) {
    while(!TXSTAbits.TRMT); // Wait until buffer is empty
    TXREG = data;
}

void UART_Write_Text(char* text) {
    while(*text) UART_Write(*text++);
}

void ADC_Init(void) {
    ADCON1 = 0x0E;   // Configure RA0/AN0 as analog, rest digital
    ADCON2 = 0xA9;   // Right justified, 8TAD, Fosc/8
    ADCON0 = 0x01;   // Enable ADC, select channel AN0
}

unsigned int ADC_Read(void) {
    ADCON0bits.GO = 1;              // Start conversion
    while(ADCON0bits.GO);          // Wait for conversion
    return ((ADRESH << 8) + ADRESL);
}

void main(void) {
    unsigned int adc_value;
    float temp_c;
    char buffer[16];

    UART_Init();
    ADC_Init();

    while(1) {
        adc_value = ADC_Read();
        temp_c = (adc_value * 5.0 / 1023.0) * 100.0;  // LM35: 10mV per °C

        sprintf(buffer, "Temp: %.2f C\r\n", temp_c);
        UART_Write_Text(buffer);
        __delay_ms(1000);
    }
}
