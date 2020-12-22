/*
 * keypad.h
 *
 *  Created on: 2020Äê12ÔÂ16ÈÕ
 *      Author: Neowless
 */

#ifndef PERIPHERAL_KEYPAD_H_
#define PERIPHERAL_KEYPAD_H_

#define COLPORT                  GPIO_PORTD_BASE;
#define ROWPORT                  GPIO_PORTE_BASE;

#define COL1                     GPIO_PIN_0;
#define COL2                     GPIO_PIN_1;
#define COL3                     GPIO_PIN_2;
#define ROW1                     GPIO_PIN_0;
#define ROW2                     GPIO_PIN_1;
#define ROW3                     GPIO_PIN_2;

void PE_Int(void);
void ButtonEInit(void);


#endif /* PERIPHERAL_KEYPAD_H_ */
