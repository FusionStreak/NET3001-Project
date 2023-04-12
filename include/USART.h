/**
 * @file USART.h
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief USART Library
 * @version 0.1
 * @date 2023-02-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#define MAX_TEXT 200   // Max string size
#define BAUD_RATE 0x67 // 9600 Baud rate

#include <Arduino.h>

/**
 * @brief Initialise the arduino for USART communication
 *
 */
void USART_init();

/**
 * @brief Send data over USART, 1 byte
 *
 * @param data The data to be sent
 */
void USART_send(unsigned char data);

/**
 * @brief Send a string over USART
 *
 * @param str The string to be sent
 */
void USART_print(char *str);

/**
 * @brief Read a byte from USART
 *
 * @return unsigned char
 */
unsigned char USART_read();

/**
 * @brief Reads a string from USART
 *
 * @param buffer The buffer to store the string
 */
void USART_get_string(char *buffer);