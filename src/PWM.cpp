/**
 * @file PWM.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief PWM Library
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <PWM.h>

void PWM_init(byte timer, byte channel, byte mode, byte scalar)
{
    switch (timer)
    {
    case timer0:
        PWM_timer0(channel, mode, scalar);
        break;
    case timer1:
        PWM_timer1(channel, mode, scalar);
        break;
    case timer2:
        PWM_timer2(channel, mode, scalar);
        break;
    default:
        break;
    }
}

void PWM_timer0(byte channel, byte mode, byte scalar)
{
    TCCR0B |= scalar;
    switch (channel)
    {
    case A:
        DDRD |= (1 << PD6);
        if (mode == fastNormal)
        {
            TCCR0A |= 0b10000011;
        }
        break;
    case B:
        DDRD |= (1 << PD5);
        if (mode == fastNormal)
        {
            TCCR0A |= 0b00100011;
        }
        break;
    default:
        break;
    }
    TCNT0 = 0;
}

void PWM_timer1(byte channel, byte mode, byte scalar)
{
    TCCR1B |= scalar; // Setting Timer1 prescalar
    switch (channel)
    {
    case A:
        DDRB |= (1 << PB1);  // Setting Output pin for OCR1A
        if (mode == fastICR) // If FastPWM with ICR, default to ~50 Hz signal for servos
        {
            TCCR1A |= 0b10000010; // Setting Channel and WGM bits
            TCCR1B |= 0b00011000; // Setting WGM bits
            ICR1 = 4999;
        }
        break;
    case B:
        if (mode == fastICR)
        {
            TCCR1A |= 0b00100010; // Setting Channel and WGM bits
            TCCR1B |= 0b00011000; // Setting WGM bits
        }
        break;
    default:
        break;
    }
    TCNT1 = 0; // Setting
}

void PWM_timer2(byte channel, byte mode, byte scalar)
{
    TCCR2B |= scalar;
    switch (channel)
    {
    case A:
        DDRB |= (1 << PB3);
        if (mode == fastNormal)
        {
            TCCR2A |= 0b10000011;
        }
        break;
    case B:
        DDRD |= (1 << PD3);
        if (mode == fastNormal)
        {
            TCCR2A |= 0b00100011;
        }
        break;
    default:
        break;
    }
    TCNT2 = 0;
}

void PWM_timer0_setDutyCyle(byte channel, uint16_t value)
{
    switch (channel)
    {
    case A:
        OCR0A = value;
        break;
    case B:
        OCR0B = value;
        break;
    default:
        break;
    }
}

void PWM_timer1_setDutyCyle(byte channel, uint16_t value)
{
    switch (channel)
    {
    case A:
        OCR1A = value;
        break;
    case B:
        OCR1B = value;
        break;
    default:
        break;
    }
}

void PWM_timer2_setDutyCyle(byte channel, uint16_t value)
{
    switch (channel)
    {
    case A:
        OCR2A = value;
        break;
    case B:
        OCR2B = value;
        break;
    default:
        break;
    }
}

void test_init()
{
    TCCR0B |= timer0_64;
    TCCR0A |= 0b10100011;

    TCCR1A |= 0b10000010;
    TCCR1B |= 0b00011011;
    ICR1 = 4999;
    TCNT1 = 0;

    TCCR2B |= timer2_64;
    TCCR2A |= 0b00100011;

    DDRD |= (1 << PD3);
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD6);
}