/*
 * my_pwm.c
 *
 *  Created on: 2020��12��21��
 *      Author: Neowless
 */
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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void PWMInit(void)
{
    //����PWMʱ�ӣ�����USEPWMDIV��Ƶ����
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);                                                                                                 //PWMʱ�� 16M

    //ʹ��ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);         //ʹ��PWMģ��1ʱ��        //ʹ��GPIOFʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //ʹ�����Ÿ���PWM����
    GPIOPinTypePWM(GPIO_PORTA_BASE,GPIO_PIN_7);

    //PWM�źŷ���
    GPIOPinConfigure(GPIO_PA7_M1PWM3);//PF3->PWMģ��1�ź�7

    //����PWM������
    //ģ��1->������3->���¼�������ͬ��
    PWMGenConfigure(PWM1_BASE,PWM_GEN_1,PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);

    //����PWM����
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_1,640);     //64*10^3/16/10^6=4ms

    //����PWMռ�ձ�
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_3,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*0.01);      //�Ƚ�ֵΪ�ķ�֮���ܼ���ֵ��75%

    //ʹ��PWMģ��1���
    PWMOutputState(PWM1_BASE,PWM_OUT_3_BIT,true);

    //ʹ��PWM������
    PWMGenEnable(PWM1_BASE,PWM_GEN_1);

}



/******************************************************************************************************************
*������: SetDuty(uint32_t ui32Base,uint32_t ui32PWMOut,float duty)
*��   ����PWM��ʼ������
*��   �룺PWMģ���š��źű�š�ռ�ձ�
******************************************************************************************************************/
void SetDuty(uint32_t ui32Base,uint32_t ui32PWMOut,float duty)
{
        uint32_t ui32Gen;
        uint32_t ui32OutBits;

        switch(ui32PWMOut)
        {
            case PWM_OUT_0: ui32Gen=PWM_GEN_0,ui32OutBits=PWM_OUT_0_BIT;    break;
            case PWM_OUT_1: ui32Gen=PWM_GEN_0,ui32OutBits=PWM_OUT_1_BIT;    break;
            case PWM_OUT_2: ui32Gen=PWM_GEN_1,ui32OutBits=PWM_OUT_2_BIT;    break;
            case PWM_OUT_3: ui32Gen=PWM_GEN_1,ui32OutBits=PWM_OUT_3_BIT;    break;
            case PWM_OUT_4: ui32Gen=PWM_GEN_2,ui32OutBits=PWM_OUT_4_BIT;    break;
            case PWM_OUT_5: ui32Gen=PWM_GEN_2,ui32OutBits=PWM_OUT_5_BIT;    break;
            case PWM_OUT_6: ui32Gen=PWM_GEN_3,ui32OutBits=PWM_OUT_6_BIT;    break;
            case PWM_OUT_7: ui32Gen=PWM_GEN_3,ui32OutBits=PWM_OUT_7_BIT;    break;
        }

    //����ռ�ձ�
    PWMPulseWidthSet(ui32Base, ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen)*duty);
    PWMOutputState(ui32Base, ui32OutBits, true);
    //ʹ�ܷ�����ģ��
    PWMGenEnable(ui32Base, ui32Gen);
}
