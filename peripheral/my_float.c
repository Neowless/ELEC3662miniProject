/*
 * my_float.c
 *
 *  Created on: 2020Äê12ÔÂ21ÈÕ
 *      Author: Neowless
 */


#include <stdint.h>
#include "my_float.h"
#include <stdlib.h>
#include <math.h>

void Float_Number_Render(char line, char collum, float x)
{
    char floatChar [13];
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
    while(fabs(x)<1)
    {
        x = 10*x;
        counter--;
    }
    while(fabs(x)>10)
    {
        x = x/10;
        counter++;
    }
    Effective = fabs(x*1000000)+0.5; // transform it into integer
    Exponential = counter;
    //
    // Check whether the float is Positive or Negative to determine the first CHAR
    //
    if(x>0){floatChar[0]=0x20;}// none
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
            Cache = fabs(x)*pow(10,i+1);
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
    char*p = &floatChar;
    LCD_PrintLnCount(line, p);


    return(NUMBERCOUNTER);
}
