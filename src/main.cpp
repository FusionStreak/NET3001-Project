/**
 * @file main.cpp
 * @author Madeline Quang (madelinequang@cmail.carleton.ca)
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief NET 3001 - Final Project
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Arduino.h>
#include <USART.h>
#include <ShiftRegister.h>
#include <INT0.h>
#include <LCD.h>
#include <ADC.h>
#include <PWM.h>

#define Trigger_pin PC0 /* Trigger pin */

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++; /* Increment Timer Overflow count */
}

int main()
{
	// Add at the beginning of each project to enable debugging
#ifdef __DEBUG__
	dbg_start();
#endif

	// Setup
	USART_init();
	init_LCD();
	PWM_init(timer0, A, fastNormal, 64);
	PWM_init(timer0, B, fastNormal, 64);
	PWM_init(timer2, B, fastNormal, 64);

	LCD_command(1);
	LCD_command(0x01);
	LCD_string("HELLO");

	char string[10];
	long count;
	double distance;

	DDRC = 0x01;		 /* Make trigger pin as output */
	DDRB &= ~(1 << PB0); /* Make echo pin as input */
	PORTB = 0x01;		 /* Turn on Pull-up */

	USART_print("Ultrasonic");
	USART_send('\n');

	sei();				   /* Enable global interrupt */
	TIMSK1 = (1 << TOIE1); /* Enable Timer1 overflow interrupts */
	TCCR1A = 0;			   /* Set all bit to zero Normal operation */

	while (1)
	{

		PORTC |= (1 << Trigger_pin); /* Give 10us trigger pulse on trig. pin to HC-SR04 */
		_delay_us(10);
		PORTC &= (~(1 << Trigger_pin));

		TCNT1 = 0;		   /* Clear Timer counter */
		TCCR1B = 0x41;	   /* Setting to capture rising edge, No pre-scaler*/
		TIFR1 = 1 << ICF1; /* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1 << TOV1; /* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) on PortB PB0 */

		while ((TIFR1 & (1 << ICF1)) == 0)
			;			   /* Wait for rising edge */
		TCNT1 = 0;		   /* Clear Timer counter */
		TCCR1B = 0x01;	   /* Setting for capture falling edge, No pre-scaler */
		TIFR1 = 1 << ICF1; /* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1 << TOV1; /* Clear Timer Overflow flag */
		TimerOverflow = 0; /* Clear Timer overflow count */

		while ((TIFR1 & (1 << ICF1)) == 0)
			;									/* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow); /* Take value of capture register */
		/* 16MHz Timer freq, sound speed =343 m/s,  17150 x Timer value * 0.0625 x 10 ^ -6 = Timer value / 932.8*/
		distance = (double)count / 932.8;

		dtostrf(distance, 2, 2, string); /* Convert distance into string */
		strcat(string, " cm   ");
		USART_print("Dist = ");
		USART_print(string); /* Print distance on LDC16x2 */
		USART_send('\n');
		_delay_ms(200);

		if (distance > 50)
		{
			PWM_timer0_setDutyCyle(B,250);
		}
		else if (distance < 50 && distance > 30)
		{
			PWM_timer0_setDutyCyle(A,100);
			PWM_timer0_setDutyCyle(B,100);
		}
		else if (distance < 10)
		{
			PWM_timer0_setDutyCyle(A,250);

		}
	}
}
