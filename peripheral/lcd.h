/*
 * lcd.h
 *
 *  Created on: 2020Äê12ÔÂ18ÈÕ
 *      Author: Neowless
 */

#ifndef PERIPHERAL_LCD_H_
#define PERIPHERAL_LCD_H_

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB

#define LCDCONFIGPORT         GPIO_PORTA_BASE
#define LCDCONFIGPORTENABLE   SYSCTL_PERIPH_GPIOA

#define RS              GPIO_PIN_3
#define E               GPIO_PIN_2


#define D4              GPIO_PIN_2
#define D5              GPIO_PIN_3
#define D6              GPIO_PIN_4
#define D7              GPIO_PIN_5


void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char
void LCD_Show_uint32(uint32_t xx);
void LCD_Cursor_uint32(uint32_t Position);
void LCD_Clear(void);                               //Clear the screen
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_PrintJustify(char i, char *s, char *d);    //Print specific line floated left and floated right text
void LCD_Cursor(char x, char y);                    //Set cursor
void LCD_PrintLnCount(char i, char *s);


#endif /* PERIPHERAL_LCD_H_ */
