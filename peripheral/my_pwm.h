/*
 * my_pwm.h
 *
 *  Created on: 2020��12��21��
 *      Author: Neowless
 */

#ifndef PERIPHERAL_MY_PWM_H_
#define PERIPHERAL_MY_PWM_H_

void PWMInit(void);
void SetDuty(uint32_t ui32Base,uint32_t ui32PWMOut,float duty);

#endif /* PERIPHERAL_MY_PWM_H_ */
