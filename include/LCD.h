/**
 * @file LCD.h
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Set of functions to control an LCD display, 4-bit mode
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <Arduino.h>

typedef enum
{
    clear = 0x01,
    entry = 0x06,
    dispOn = 0x0C,
    dispOnCursor = 0x0E,
    returnFirst = 0x80,
    returnSecond = 0xC0,
    cursorLeft = 0x10,
    cursorRight = 0x14,
    shiftLeft = 0x18,
    shiftRight = 0x1C,
    init2L8Bit = 0x38,
    init2L4Bit = 0x28,
    init1L8Bit = 0x30,
    init1L4Bit = 0x20
} command;

/**
 * @brief Initialises the LCD Display
 *
 */
void init_LCD();

/**
 * @brief Sends a command to LCD display
 *
 * @param command
 */
void LCD_command(uint8_t command);

/**
 * @brief Send 8-bit data to LCD display, and displays it
 *
 * @param data
 */
void LCD_data(uint8_t data);

/**
 * @brief Sends a set of chars to LCD displays, and displays them
 *
 * @param str
 */
void LCD_string(char *str);

/**
 * @brief Sends the enable pin pulse
 *
 */
void LCD_enable_pulse();

/**
 * @brief Write the higher nibble of data to LCD
 * 
 * @param data the data to me transmitted
 * @param isCommand is this a command or not
 */
void LCD_write_nibble(uint8_t data, uint8_t isCommand);

/**
 * @brief Reloads the LCD if it bugs out
 * 
 */
void LCD_reload();