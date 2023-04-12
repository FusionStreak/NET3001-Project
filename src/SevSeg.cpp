/**
 * @file SevSeg.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Seven Segment Display control
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <SevSeg.h>

/**
 * Pin layout
 * PD0 - DP
 * PD1 - C
 * PD2 - D
 * PD3 - E
 * PD4 - G
 * PD5 - F
 * PD6 - A
 * PD7 - B
 */

// The values corresponding values to display 0-9, A-F using this pin out
//                       0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F
const int values[16] = {0xEE, 0x82, 0xDC, 0xD6, 0xB2, 0x76, 0x7E, 0xC2, 0xFE, 0xF6, 0xFA, 0x3E, 0x6C, 0x9E, 0x7C, 0x78};

void clear()
{
    PORTD = 0;
}

void setupDisplay()
{
    DDRD = 255; // Set PORT D Direction to output
    clear();    // Clear PORT D output
}

void display(int digit)
{
    // If digit is outside range
    if (digit < 0 || digit > 15)
    {
        // Clear the display and return
        clear();
        return;
    }
    // Display the value
    PORTD = values[digit];
}
