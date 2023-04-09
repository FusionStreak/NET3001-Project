/**
 * @file ADC.cpp
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief ADC Lib
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <ADC.h>

void ADC_init(){										
	DDRC = 0x00;	        // Make ADC port as input 
	ADCSRA |= (1<<ADEN) | (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0);//0xA7; / Enable ADC, with auto-trigger and freq/128  
	ADMUX = 0x40;           // Vref: Avcc, ADC channel: 0 
	DIDR0 = 0x01;			//disable digital pin C0 optional

}

int ADC_read(byte channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   // set input channel to read 
	ADCSRA |= (1<<ADSC);               // Start ADC conversion 
	while (!(ADCSRA & (1<<ADSC)));     // Wait until end of conversion by polling ADC interrupt flag or when ADSC is 0 */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}
