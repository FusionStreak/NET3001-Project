/**
 * @file ADC.h
 * @author Sayfullah Eid (sayfullaheid@cmail.carleton.ca)
 * @brief ADC Lib
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>

void ADC_init();

int ADC_read(byte channel);