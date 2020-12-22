#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"               //Register Definitions
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/fpu.h"
#include "inc/hw_types.h"
#include "on_board_led.h"
#include "usart.h"
#include "keypad.h"
#include "lcd.h"
#include "my_pwm.h"
#include "my_float.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void SysTick_Wait(unsigned long delay);


int main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);//running at 80 MHz
    USARTInit();
    SysTickEnable();
    On_Board_LEDInit();
    ButtonEInit();
    FPUEnable();
    GPIOIntRegister(GPIO_PORTE_BASE, PE_Int);
    GPIOIntEnable(GPIO_PORTE_BASE, 0x0F);
    IntEnable(INT_GPIOE);
    On_Board_LEDWrite(RED|GREEN|BLUE);
    IntMasterEnable();
    LCD_init();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_6, 0x00);
    PWMInit();
    SetDuty(PWM1_BASE,PWM_OUT_3,0.4);

    float x=-0.0125673;
    uint32_t floatChar [13];
    int Exponential = 0;
    int i = 0;
    int counter = 0;
    int Effective = 0;
    int NUMBERCOUNTER = 0;
    counter = 0;
    int Cache;
    //
    //Get the effective value and exponential, the basic form of the float expressed in the 1602 is +- A.xxxxxxe+-EEE
    //
    while(abs(x)<1)
    {
        x = 10*x;
        counter--;
    }
    while(abs(x)>10)
    {
        x = x/10;
        counter++;
    }
    Effective = abs(x*1000000);
    Exponential = counter;
    //
    // Check whether the float is Positive or Negative to determine the first CHAR
    //
    if(x>0){floatChar[0]=0x20;}
    else{floatChar[0]=0x2D;}
    //
    // If the exponential value is less than -1 or larger than 3, the value of the float value should be expressed as scientific notation.
    //
    if(Exponential<-1|Exponential>=4)
    {
        floatChar[1] = (Effective/1000000)+0x30;//This is the value of A
        floatChar[2] = 0x2E;// This is the dot

        for(i = 0; i < 6; i++)
        {
            Cache = abs(x * pow(10,i+1));
            floatChar[i+3] = 0x30 + Cache%10;
        }
        floatChar[9] = 0x65;// This is e
        if(Exponential>0)// Determine the +- of the exponential value
        {
            floatChar[10] = 0x2B;//+
        }
        else
        {
            floatChar[10] = 0x2D;//-
        }

        if (abs(Exponential)<10)
        {
            floatChar[11] = abs(Exponential)+0x30;
            NUMBERCOUNTER = 12;
        }
        else if (abs(Exponential)<100)
        {
            floatChar[11] = abs(Exponential/10)+0x30;
            floatChar[12] = abs(Exponential%10)+0x30;
            NUMBERCOUNTER = 13;
        }
        else
        {
            floatChar[11] = 1;
            floatChar[12] = abs(Exponential/10)+0x26;
            floatChar[13] = abs(Exponential%10)+0x36;
            NUMBERCOUNTER = 14;
        }
    }
    else//Expressed as normal standard(0.x-1234)
    {
        if(Exponential==-1)
        {
            floatChar[1] = 0x30;
            floatChar[2] = 0x2E;
            for(i = 0; i < 7; i++)
            {
                Cache = abs(x * pow(10,i));
                floatChar[i+3] = 0x30 + Cache%10;
                NUMBERCOUNTER = 10;
            }
        }
        else
        {
            for(i = 0; i < 7; i++)
            {
                Cache = abs(x * pow(10,i));
                floatChar[i+1] = 0x30 + Cache%10;
                NUMBERCOUNTER = 9;
            }

            for(i = 0; i < 6 - Exponential; i++)
            {
                floatChar[Exponential+3+i] = floatChar[Exponential+2+i];
            }
            floatChar[Exponential+2] = 0x2E;
        }


    }
    char* p;
    p = &floatChar;

    LCD_PrintLnCount(0, p, NUMBERCOUNTER);

    while(1)
    {
        ;
    }


}


void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}










