/*
 * lcd.c
 *
 *  Created on: 2020Äê12ÔÂ18ÈÕ
 *      Author: Neowless
 */


#include <stdbool.h>
#include <stdint.h>
#include <lcd.h>

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include "inc/tm4c123gh6pm.h"

void LCD_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, D4|D5|D6|D7);
        SysCtlPeripheralEnable(LCDCONFIGPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDCONFIGPORT, RS|E);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDCONFIGPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  D4 | D5 );
        GPIOPinWrite(LCDCONFIGPORT, E, E);
        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  D4 | D5 );
        GPIOPinWrite(LCDCONFIGPORT, E, E);
        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  D4 | D5 );
        GPIOPinWrite(LCDCONFIGPORT, E, E);
        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  D5 );
        GPIOPinWrite(LCDCONFIGPORT, E, E);
        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);

        SysCtlDelay(50000);


        LCD_Command(0x0F); //Turn on Lcd
        LCD_Clear(); //Clear screen

}

void LCD_Command(unsigned char c) {
        uint32_t temp;
        uint32_t cache;
        temp = (c & 0xF0)>>2;
        cache = GPIO_PORTB_DATA_R&0xC3; //Get the value of other bits
        GPIO_PORTB_DATA_R = cache|temp;

        GPIO_PORTA_DATA_R |= 0x04;// E = 1
        GPIO_PORTA_DATA_R &= 0xF7;// RS = 0

        SysCtlDelay(50000);

        GPIO_PORTA_DATA_R &= 0xFB; // E = 0

        SysCtlDelay(50000);

        temp = (c & 0x0F)<<2;
        cache = GPIO_PORTB_DATA_R&0xC3; //Get the value of other bits
        GPIO_PORTB_DATA_R = cache|temp;
        GPIO_PORTA_DATA_R &= 0xF7;// RS = 0
        GPIO_PORTA_DATA_R |= 0x04;// E = 1

        SysCtlDelay(10);

        GPIO_PORTA_DATA_R &= 0xFB; // E = 0

        SysCtlDelay(50000);

}

void LCD_Show(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xF0)>>2 );
        GPIOPinWrite(LCDCONFIGPORT, RS, RS);
        GPIOPinWrite(LCDCONFIGPORT, E, E);

        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);
        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0F) << 2 );
        GPIOPinWrite(LCDCONFIGPORT, RS, RS);
        GPIOPinWrite(LCDCONFIGPORT, E, E);

        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);
        SysCtlDelay(50000);
}


void LCD_Show_uint32(uint32_t xx) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (xx & 0xF0)>>2 );
        GPIOPinWrite(LCDCONFIGPORT, RS, RS);
        GPIOPinWrite(LCDCONFIGPORT, E, E);

        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);
        SysCtlDelay(50);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (xx & 0x0F) << 2 );
        GPIOPinWrite(LCDCONFIGPORT, RS, RS);
        GPIOPinWrite(LCDCONFIGPORT, E, E);

        SysCtlDelay(10);
        GPIOPinWrite(LCDCONFIGPORT, E, 0x00);
        SysCtlDelay(50);
}

void LCD_Cursor(char x, char y){

    if (x==0) {
        LCD_Command(0x80 + (y % 16));
        return;
    }
    LCD_Command(0xC0 + (y % 16));

}

void LCD_Cursor_uint32(uint32_t Position)
{
    uint32_t x = 0xF0&Position;
    uint32_t y = 0x0F&Position;
    if (x==0x00)
    {
        LCD_Command(0x80 + y);
        return;
    }
    else if(x==0x10)
    {
        LCD_Command(0xC0 + y);
    }

}

void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(10);
}




void LCD_PrintJustify(char i, char *s, char *d) {
    if (i==0) {
        for (i=0; i<strlen(s); i++) {
            LCD_Cursor(0, i);
            LCD_Show(s[i]);
        }
        for (i=0; i<strlen(d); i++) {
            LCD_Cursor(0, 15-i);
            LCD_Show(d[strlen(d)-i-1]);
        }
        LCD_Command(0xC0 + 16);
        return;
    }
    for (i=0; i<strlen(s); i++) {
        LCD_Cursor(1, i);
        LCD_Show(s[i]);
    }
    for (i=0; i<strlen(d); i++) {
        LCD_Cursor(1, 15-i);
        LCD_Show(d[strlen(d)-i-1]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}



void LCD_Print(char *s, char *d) {
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(s)) {
            LCD_Cursor(0,j);
            LCD_Show(s[j]);
        }
        if (j<strlen(d)) {
            LCD_Cursor(1,j);
            LCD_Show(d[j]);
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}


void LCD_PrintLn(char i, char *s) {
    LCD_Cursor(i, 0);
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xD0); //Hide cursor
}

void LCD_PrintLnCount(char i, char *s)
{
    LCD_Cursor(i, 0);
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xD0); //Hide cursor
}

