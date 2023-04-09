/**
 * @file SevSeg.hpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Seven Segment Display control
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Clear PORT D output signals
 *
 */
void clear();

/**
 * @brief Set up PORT D to output and and clear port output
 *
 */
void setupDisplay();

/**
 * @brief Display a single hexadecimal digit on to Sev Segment display.
 * Will clear the display if 0 > digit or 15 < digit
 *
 * @param digit The digit to be display as `int` [0-15]
 */
void display(int digit);