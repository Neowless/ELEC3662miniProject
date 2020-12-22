/*
 * on_board_led.h
 *
 *  Created on: 2020Äê12ÔÂ13ÈÕ
 *      Author: Neowless
 */

#ifndef PERIPHERAL_ON_BOARD_LED_H_
#define PERIPHERAL_ON_BOARD_LED_H_

#define CLOSE                     0x00000000  // PF
#define RED                       0x00000002  // PF1
#define BLUE                      0x00000004  // PF2
#define GREEN                     0x00000008  // PF3

void On_Board_LEDInit(void);
extern void On_Board_LEDWrite(uint32_t ui32Colour);

#endif /* PERIPHERAL_ON_BOARD_LED_H_ */
