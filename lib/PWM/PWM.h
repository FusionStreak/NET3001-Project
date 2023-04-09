/**
 * @file PWM.h
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief PWM Library
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <Arduino.h>

typedef enum
{
    phaseInverted,
    fastInverted,
    phaseNormal,
    fastNormal,
    fastICR
} modes;

typedef enum
{
    timer0_1 = 0b001,
    timer0_8 = 0b010,
    timer0_64 = 0b011,
    timer0_256 = 0b100,
    timer0_1024 = 0b101,
    timer1_1 = 0b001,
    timer1_8 = 0b010,
    timer1_64 = 0b011,
    timer1_256 = 0b100,
    timer1_1024 = 0b101,
    timer2_1 = 0b001,
    timer2_8 = 0b010,
    timer2_32 = 0b011,
    timer2_64 = 0b100,
    timer2_128 = 0b101,
    timer2_256 = 0b110,
    timer2_1024 = 0b111
} scalar;

typedef enum
{
    A = 'A',
    B = 'B'
} channel;

typedef enum
{
    timer0 = 0,
    timer1 = 1,
    timer2 = 2
} timer;

/**
 * @brief Initialises a PWM signal based on the parameters provided
 * 
 * @warning The scalar is used for the entire timer, not per channel
 * 
 * @param timer The timer to use [0, 1, 2]
 * @param channel The channel to use ['A', 'B']
 * @param mode The PWM mode to use, look at enum modes
 * @param scalar The pre-scalar to use, look at enum scalar
 */
void PWM_init(byte timer, byte channel, byte mode, byte scalar);

/**
 * @brief Used to initialise Timer0 on provided channel and paramaters
 * 
 * @warning The scalar is used for the entire timer, not per channel
 * 
 * @param channel The channel to use ['A', 'B']
 * @param mode The PWM mode to use, look at enum modes
 * @param scalar The pre-scalar to use, look at enum scalar
 */
void PWM_timer0(byte channel, byte mode, byte scalar);

/**
 * @brief Used to initialise Timer1 on provided channel and paramaters
 * 
 * @warning The scalar is used for the entire timer, not per channel
 * 
 * @param channel The channel to use ['A', 'B']
 * @param mode The PWM mode to use, look at enum modes
 * @param scalar The pre-scalar to use, look at enum scalar
 */
void PWM_timer1(byte channel, byte mode, byte scalar);

/**
 * @brief Used to initialise Timer2 on provided channel and paramaters
 * 
 * @warning The scalar is used for the entire timer, not per channel
 * 
 * @param channel The channel to use ['A', 'B']
 * @param mode The PWM mode to use, look at enum modes
 * @param scalar The pre-scalar to use, look at enum scalar
 */
void PWM_timer2(byte channel, byte mode, byte scalar);

/**
 * @brief Set the duty cycle of a PWM channel on Timer0
 * 
 * @param channel The channel to use ['A', 'B']
 * @param value The value to set
 */
void PWM_timer0_setDutyCyle(byte channel, uint16_t value);

/**
 * @brief Set the duty cycle of a PWM channel on Timer1
 * 
 * @param channel The channel to use ['A', 'B']
 * @param value The value to set
 */
void PWM_timer1_setDutyCyle(byte channel, uint16_t value);

/**
 * @brief Set the duty cycle of a PWM channel on Timer2
 * 
 * @param channel The channel to use ['A', 'B']
 * @param value The value to set
 */
void PWM_timer2_setDutyCyle(byte channel, uint16_t value);

void test_init();