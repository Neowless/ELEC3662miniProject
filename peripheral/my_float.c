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


// Check the float is a POSITIVE(0) or NEGATIVE(1) number
int float_PN(uint32_t x)
{
    return((x&0x80000000)>>31);
}

// Check the Exponential number in Binary
int float_EXP(uint32_t x)
{
    return(((x&0x7F800000)>>23) -127);
}

//Check the effective value
uint32_t float_EFF(uint32_t x)
{
    return((x&0x007FFFFF)|0x00800000);
}
int float_Integer(uint32_t x)
{
    int EXP = float_EXP(x);
    uint32_t EFF = float_EFF(x);
    int EFFInt = 0;
    if(EXP<0)// The dot should move to left.
    {
        return(0);
    }
    else if (EXP>23)// The dot is after the whole number.
    {
        EFFInt = EFF;
        EFFInt = EFFInt*pow(2,EXP-23);
        return(EFFInt);
    }
    return(EFF>>(23-EXP));// The dot moves to right.
}

int INTLength(int x)
{
    int counter = 0;
    while(x)
    {
        x = x/10;
        counter++;
    }
    return(counter);
}

char *float2char(float x)
{
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
    LCD_PrintLnCount(0, p, NUMBERCOUNTER);
    return(p);
}
