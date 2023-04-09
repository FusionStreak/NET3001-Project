#include "ShiftRegister.h"
/**
 * @file ShiftRegister.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Shift Register Library (74HC595)
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023
 *
 */

void Shift_init(ShiftRegister shift)
{
    DDRD |= (1 << shift.dataPin) | (1 << shift.clockPin) | (1 << shift.latchPin);
}

void shiftOut(ShiftRegister shift, byte value, bool order)
{
    PORTD &= ~(1 << shift.latchPin);

    for (byte i = 0; i < 8; i++)
    {
        if (order)
        {
            if ((value & 128) != 0)
            {
                PORTD |= (1 << shift.dataPin);
            }
            else
            {
                PORTD &= ~(1 << shift.dataPin);
            }
            value <<= 1; // shift the data to left to get the next MSB
        }
        else
        {
            if ((value & 1)) // if the bit is 1
            {
                PORTD |= (1 << shift.dataPin); // send one
            }
            else
            {
                PORTD &= ~(1 << shift.dataPin); // send 0
            }
            value >>= 1; // shift the data to right to get the next LSB
        }

        // Create a clock pulse
        PORTD |= (1 << shift.clockPin);
        PORTD &= ~(1 << shift.clockPin);
    }

    PORTD |= (1 << shift.latchPin);
}
