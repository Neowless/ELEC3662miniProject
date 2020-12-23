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

    float x = -213456789932;
    char p = Float_Number_Render(0, 1, x);


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










