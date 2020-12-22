/*
 * keypad.c
 *
 *  Created on: 2020Äê12ÔÂ16ÈÕ
 *      Author: Neowless
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "on_board_led.h"
#include "keypad.h"

void ButtonEInit(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTD|SYSCTL_GPIOHBCTL_PORTE ;

    //
    //Set PORTE PIN[0:3] as pull-up input pull-up(COLUMNS)
    //
    GPIO_PORTE_LOCK_R = 0x4C4F434B;   //unlock GPIOCR
    GPIO_PORTE_CR_R |= 0x0F;          //unlock GPIOAFSEL, GPIOPUR, GPIOPDR
    GPIO_PORTE_DR2R_R |= 0x0F;
    GPIO_PORTE_DR4R_R |= 0x00;
    GPIO_PORTE_DR8R_R |= 0x00;        //Current limitation
    GPIO_PORTE_SLR_R |= 0x00;         //Slew rate control only available in 8ma mode
    GPIO_PORTE_ODR_R |= 0x00;         //Open Drain
    GPIO_PORTE_PUR_R |= 0x0F;         //Pull-up
    GPIO_PORTE_PDR_R |= 0x00;         //Pull-down
    GPIO_PORTE_DEN_R |= 0x0F;         //Enable Digital Function
    GPIO_PORTE_AMSEL_R = 0x00;        //Disable analog function
    GPIO_PORTE_DIR_R = 0x00;          //Set the direction
    GPIO_PORTE_AFSEL_R = 0x00;

    //
    //Set PORTD PIN[0:3] as output(ROW)
    //
    GPIO_PORTD_LOCK_R = 0x4C4F434B;   //unlock GPIOCR
    GPIO_PORTD_CR_R |= 0x0F;          //unlock GPIOAFSEL, GPIOPUR, GPIOPDR
    GPIO_PORTD_DR2R_R |= 0x0F;
    GPIO_PORTD_DR4R_R |= 0x00;
    GPIO_PORTD_DR8R_R |= 0x00;        //Current limitation
    GPIO_PORTD_SLR_R |= 0x00;         //Slew rate control only available in 8ma mode
    GPIO_PORTD_ODR_R |= 0x00;         //Open Drain
    GPIO_PORTD_PUR_R |= 0x00;         //Pull-up
    GPIO_PORTD_PDR_R |= 0x00;         //Pull-down
    GPIO_PORTD_DEN_R |= 0x0F;         //Enable Digital Function
    GPIO_PORTD_AMSEL_R = 0x00;        //Disable analog function
    GPIO_PORTD_DIR_R = 0x0F;          //Set the direction
    GPIO_PORTD_AFSEL_R = 0x00;        //Multiple function selection
    GPIO_PORTD_DATA_R &= 0xF0;        //Set the out put

    //
    //PORTE interrupt configuration
    //
    GPIO_PORTE_IBE_R |= 0x00;         //Single edge
    GPIO_PORTE_IS_R |= 0x00;          //Edge or level
    GPIO_PORTE_IEV_R |= 0x00;         //Detect rising edges or high levels, falling edges or low levels

}

void PE_Int(void)
{
    uint32_t Col = GPIO_PORTE_RIS_R;   //Raw interrupt status register, which is the column number
    uint32_t Row = 0x00;
    uint32_t Cache;
    uint32_t Temp;
    uint32_t Position;
    int i;
    SysTick_Wait(1000000);             //10ms debounce
    Cache = ~GPIO_PORTE_DATA_R;
    Cache &= 0x0000000F;               //Get the current PORTE data
    if(Col==Cache)                     //Validation of the bounce
    {
        On_Board_LEDWrite(BLUE);

        //
        //Scan which is the correct row number
        //
        for(i = 0; i < 4; i++)
        {
            Temp = 1<<i;
            Temp = ~Temp;
            Temp &= 0x0000000F;
            GPIO_PORTD_DATA_R &= 0xFFFFFFF0;
            GPIO_PORTD_DATA_R |= Temp;
            SysTick_Wait(400000);
            Cache = ~GPIO_PORTE_DATA_R; //Inverse the data, cause it is pull-uped
            Cache &= 0x0000000F;        //Delete other useless bits
            if(Cache == Col){Row = 1<<(i+4);break;} // If COL is pulled down, and this is the correct row number
            else{Row = 0x00;}
        }

        Position = Col|Row;            //Position is COL-ROW
        GPIO_PORTD_DATA_R &= 0xF0;
        switch(Position)               //Validation
        {
        case 0x11:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("1\r\n",3);
            LCD_Show_uint32(0x31);
            break;
        case 0x12:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("2\r\n",3);
            LCD_Show_uint32(0x32);
            break;
        case 0x14:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("3\r\n",3);
            LCD_Show_uint32(0x33);
            break;
        case 0x18:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("A\r\n",3);
            LCD_Show_uint32(0x41);
            break;
        case 0x21:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("4\r\n",3);
            LCD_Show_uint32(0x34);
            break;
        case 0x22:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("5\r\n",3);
            LCD_Show_uint32(0x35);
            break;
        case 0x24:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("6\r\n",3);
            LCD_Show_uint32(0x36);
            break;
        case 0x28:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("B\r\n",3);
            LCD_Show_uint32(0x42);
            break;
        case 0x41:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("7\r\n",3);
            LCD_Show_uint32(0x37);
            break;
        case 0x42:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("8\r\n",3);
            LCD_Show_uint32(0x38);
            break;
        case 0x44:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("9\r\n",3);
            LCD_Show_uint32(0x39);
            break;
        case 0x48:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("C\r\n",3);
            LCD_Show_uint32(0x43);
            break;
        case 0x81:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("*\r\n",3);
            LCD_Show_uint32(0x2A);
            break;
        case 0x82:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("0\r\n",3);
            LCD_Show_uint32(0x30);
            break;
        case 0x84:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("#\r\n",3);
            LCD_Show_uint32(0x23);
            break;
        case 0x88:
            while(!GPIO_PORTE_DATA_R&0x0F);
            USARTSend("D\r\n",3);
            LCD_Show_uint32(0x44);
            break;
        }
        SysTick_Wait(10000);
    }
    GPIO_PORTE_ICR_R = Col;            //Clear the interrupt flag
}
