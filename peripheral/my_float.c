/*
 * my_float.c
 *
 *  Created on: 2020Äê12ÔÂ21ÈÕ
 *      Author: Neowless
 */


#include <stdint.h>
#include "my_float.h"
#include <stdlib.h>


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

int float_Decimal(uint32_t x, float x_float)
{

}
