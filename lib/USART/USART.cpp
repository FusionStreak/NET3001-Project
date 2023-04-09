/**
 * @file USART.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief USART Library
 * @version 0.1
 * @date 2023-02-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <USART.h>

void USART_init()
{
    // Set Baud Rate
    UBRR0 = BAUD_RATE;
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = ((1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00));
    // Enable Receiver and Transmitter
    UCSR0B = ((1 << RXEN0) | (1 << TXEN0));
}

void USART_send(unsigned char data)
{
    // Await transmit buffer to empty
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    // Write data to transmit
    UDR0 = data;
}

void USART_print(char *str)
{
    // While not end of string
    while (*str != '\0')
    {
        // Send next character
        USART_send(*str);
        // Move to next char
        str++;
    }
}

unsigned char USART_read()
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // Return received data
    return UDR0;
}

void USART_get_string(char *buffer)
{
    char *p = buffer;
    char curr;
    do
    {
        *p = USART_read();
        USART_send(*p);
        curr = *(p++);
    } while (!((curr == '\r') || (curr == '\n'))); // If not end of string, increment pointer, continue retrieval
    *(--p) = '\0';
}