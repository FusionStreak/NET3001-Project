#include "INT0.h"
/**
 * @file INT0.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief INT0 Library
 * @version 0.1
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <INT0.h>

void INT0_init()
{
    DDRD &= ~(1 << PD2);   // Set INT0 I/O pin as input
    PORTD |= (1 << PD2);   // Set pull-up resistor on INT0 I/O pin
    EICRA |= (1 << ISC01); // set INT0 for falling edge mode
    EIMSK |= (1 << INT0);  // enable INT0
    sei();                 // enable global interrupt in SERG
}