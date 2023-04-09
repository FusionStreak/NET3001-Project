/**
 * @file ShiftRegister.h
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Shift Register Library (74HC595)
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Used to hold all the pinout connected to a Shift Register
 *
 */
struct ShiftRegister
{
    byte dataPin;  // The I/O pin connected to the data pin
    byte clockPin; // The I/O pin connected to the clock pin
    byte latchPin; // The I/O Pin connected to the latch pin
};

/**
 * @brief Initialises the I/O for use with the Shift Register
 *
 * @param shift The ShiftRegister struct conatining relavent pins
 */
void Shift_init(ShiftRegister shift);

/**
 * @brief Send data serially to Shift register
 *
 * @param shift The pinout of the Shift Register
 * @param value The vlaue to be sent to register
 * @param order The bit order {false: Least Sig First, true: Most Sig First}
 */
void shiftOut(ShiftRegister shift, byte value, bool order = LSBFIRST);