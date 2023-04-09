/**
 * @file LCD.c
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief Set of functions to control an LCD display, 4-bit mode (Modified for PORTC)
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <LCD.h>

#define RS DDB1 // Register Select is connected to PB0
#define EN DDB0 // Enable pin is connected to PB1

#define D4 DDC0 // D4 is connected to PD4
#define D5 DDC1 // D5 is connected to PD5
#define D6 DDC2 // D6 is connected to PD6
#define D7 DDC3 // D7 is connected to PD7

void init_LCD()
{
    DDRB = (1 << RS) + (1 << EN);      // Set Register Select and Enable pins to output
    PORTB &= ~((1 << RS) + (1 << EN)); // Set RS and EN to low

    DDRC |= 0x0F; // Set pins for LCD data/command to output

    LCD_reload();

    LCD_command(init2L4Bit);
    LCD_command(entry);
    LCD_command(clear);
    LCD_command(dispOnCursor);
}

void LCD_command(uint8_t comm)
{
    LCD_write_nibble(comm, 1);
    LCD_write_nibble((comm << 4), 1);
    if (comm == 0x01)
        _delay_ms(5); // Clear command needs extra time to process
}

void LCD_data(uint8_t data)
{
    LCD_write_nibble(data, 0);
    LCD_write_nibble((data << 4), 0);
}

void LCD_string(char *str)
{
    // Iterate over each char in char*
    for (uint8_t i = 0; str[i] != '\0'; i++)
    {
        LCD_data(str[i]); // Send char to LCD
    }
}

void LCD_enable_pulse()
{
    PORTB |= (1 << EN);  // Set enable pin high
    PORTB &= ~(1 << EN); // Set enable pin low
    _delay_ms(2);        // Wait 2 ms for command or data to set in
}

void LCD_write_nibble(uint8_t data, uint8_t isCommand)
{
    // Set PORTD LCD pins to higher nibble of data (first 4 bits)
    PORTC = ((data & 0xF0) >> 4);

    isCommand ? PORTB &= ~(1 << RS) : PORTB |= (1 << RS);

    LCD_enable_pulse();
}

void LCD_reload()
{
    _delay_ms(100);
    LCD_write_nibble(init1L8Bit, 1);
    _delay_ms(5);
    LCD_write_nibble(init1L8Bit, 1);
    _delay_ms(1);
    LCD_write_nibble(init1L8Bit, 1);
    _delay_ms(1);
    LCD_write_nibble(init1L4Bit, 1);
    _delay_ms(1);
}