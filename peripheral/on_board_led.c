/*
 * on_board_led.c
 *
 *  Created on: 2020Äê12ÔÂ13ÈÕ
 *      Author: Neowless
 */
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "on_board_led.h"
void On_Board_LEDInit(void)
{
//  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU)
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTF;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   //unlock GPIOCR
    GPIO_PORTF_CR_R |= 0x0E;          //unlock GPIOAFSEL, GPIOPUR, GPIOPDR
    GPIO_PORTF_DR2R_R |= 0x0E;
    GPIO_PORTF_DR4R_R |= 0x00;
    GPIO_PORTF_DR8R_R |= 0x00;        //Current limitation
    GPIO_PORTF_SLR_R |= 0x00;         //Slew rate control only available in 8ma mode
    GPIO_PORTF_ODR_R |= 0x00;         //Open Drain
    GPIO_PORTF_PUR_R |= 0x00;         //Pull-up
    GPIO_PORTF_PDR_R |= 0x00;         //Pull-down
    GPIO_PORTF_DEN_R |= 0x0E;         //Enable Digital Function
    GPIO_PORTF_AMSEL_R |= 0x00;        //Disable analog function
//  GPIODirModeSet
    GPIO_PORTF_DIR_R |= 0x0E;          //Set the direction
    GPIO_PORTF_AFSEL_R |= 0x00;        //Multiple function selection
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1);
    On_Board_LEDWrite(CLOSE);
}
//
// Set the colour of the on board LED
// RED(0x02)/BLUE(0x04)/GREEN(0x08)
//
extern void On_Board_LEDWrite(uint32_t ui32Colour)
{
    GPIO_PORTF_DATA_R &= 0xF1;
    GPIO_PORTF_DATA_R |= ui32Colour;
}
