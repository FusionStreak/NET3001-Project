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
#define BUZZER PD4

// Printed strings
char msg1[] = "Distance is ";
char msg2[] = "Ultrasonic";
char dist[] = "Dist = ";
char safe[] = "SAFE";
char caution[] = "CAUTIOUS";
char danger[] = "DANGEROUS";
char stop[] = "CAR WILL STOP";

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
	PWM_init(timer0, A, fastNormal, timer0_64); // blue - timer 0 channel A
	PWM_init(timer0, B, fastNormal, timer0_64); // green - timer 0 channel B
	PWM_init(timer2, B, fastNormal, timer2_64); // red - timer 2 channel B
	DDRD |= 1 << BUZZER;						// set PC5 buzzer to output

	// output Current Values: to LCD on the first line
	LCD_command(clear);
	LCD_command(returnFirst);
	LCD_string(msg1);

	char string[10];
	long count;
	double distance;

	DDRC |= 0x01;		 /* Make trigger pin as output */
	DDRB &= ~(1 << PB0); /* Make echo pin as input */
	PORTB |= 0x01;		 /* Turn on Pull-up */

	USART_print(msg2);
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
		USART_print(dist);
		USART_print(string); /* Print distance on LDC16x2 */
		USART_send('\n');
		_delay_ms(200);

		LCD_command(returnSecond); // Move to second line

		PORTD &= ~(1 << BUZZER); // Buzzer is off

		if (distance > 20)
		{
			// green color if distance is bigger than 20
			PWM_timer0_setDutyCyle(B, 250); // green turns on
			PWM_timer0_setDutyCyle(A, 0);	// blue turns off
			PWM_timer2_setDutyCyle(B, 0);	// red turns off
			LCD_string(safe);
		}
		else if (distance < 20 && distance > 10)
		{
			// yellow color if distance between 10 and 20
			PWM_timer0_setDutyCyle(B, 255); // green turns on
			PWM_timer0_setDutyCyle(A, 0);	// blue turns off
			PWM_timer2_setDutyCyle(B, 255); // red turns on
			LCD_string(caution);
		}
		else if (distance < 10 && distance > 5)
		{
			// orange color if distance between 5 and 10
			PWM_timer0_setDutyCyle(B, 30);	// green turns on with 30
			PWM_timer0_setDutyCyle(A, 0);	// blue turns off
			PWM_timer2_setDutyCyle(B, 255); // red turns off
			LCD_string(danger);
		}
		else if (distance < 5)
		{
			// red color if distance is less than 5
			PWM_timer0_setDutyCyle(B, 0);	// green turns on
			PWM_timer0_setDutyCyle(A, 0);	// blue turns off
			PWM_timer2_setDutyCyle(B, 250); // red turns off
			LCD_string(stop);
			PORTD |= 1 << BUZZER; // buzzer is on
		}
	}
}
