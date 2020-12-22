<!--
 * @Author: your name
 * @Date: 2020-12-22 14:10:38
 * @LastEditTime: 2020-12-22 16:28:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \undefinedc:\Users\Neowless\workspace_v10\blink\README.md
-->
# ELEC3662miniProject
## Abstract
This project is based on EK-TM4C123GXL with 4*4 Keypand and 1602 LCD.<br>
The editing enviroment is based on Code Composer Studio 10.1.1 with tivaware_c_series_2_1_4_178.<br>
This project is build for ELEC 3662 course in Univerisity of Leeds.<br>
This project is only available to be referenced.<br>
Yuheng Huo reserves the right to explain the terms of the event.<br>
## Introduction
### Connection
**Keypad**

<div><img width="500" height="500" float:left src="https://github.com/Neowless/ELEC3662miniProject/blob/master/keypad.png"/></div>

In this project a matrix keypad was applied.
|  Launch Pad   | Keypad  |
|   :----:  |  :----: |
| PE0  | ROW1 |
| PE1  | ROW2 |
| PE2  | ROW3 |
| PE3  | ROW4 |
| PD0  | COL1 |
| PD1  | COL2 |
| PD2  | COL3 |
| PD3  | COL4 |

All of the pins on the keypad are directly connected to the GPIOs on the launch board, it is not of necessity to applied external pull-up voltage.

**1602 LCD**

<div><img width="500" height="244" float:left src="https://github.com/Neowless/ELEC3662miniProject/blob/master/lcd.png"/></div>

|  Launch Pad   | 1602 LCD  |
|   :----:  |  :----: |
| GND  | VSS |
| VBUS  | VDD |
| PA7  | V0 |
| PA3  | RS |
| GND  | RW |
| PA2  | E |
| PB2  | D4 |
| PB3  | D5 |
| PB4  | D6 |
| PB5  | D7 |
| +3.3V  | A |
| GND  | K |

In this project, there's no demand to get the feadback of the LCD, so the Read/Write pin on the LCD is connected to the GND.
To transmit the segment on the LCD and conserve the GPIO of the launchpad, the LCD is working in the nibble mode which means only D4-D7 are used to transfer data.
For further information about this LCD, please check the link below.
https://bbs.21ic.com/UploadFiles/2009-11/261113444198.pdf
In addition to control the contrast of the LCD, V0 port on the LCD is attached to PA7, which is controled by module 1 PWM Generator 1.

<div><img width="500" height="500" float:left src="https://github.com/Neowless/ELEC3662miniProject/blob/master/pwm.png"/></div>
