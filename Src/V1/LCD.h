/*
 * ultraSonic_driver.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Ali Mustafa
 */

#ifndef LCD_H_
#define LCD_H_
#include "LiquidCrystal.h"

//The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 15
// * LCD D5 pin to digital pin 12
// * LCD D6 pin to digital pin 14
// * LCD D7 pin to digital pin 27
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V
// * 10K resistor:
// * ends to +5V and ground
// * wiper to LCD VO pin (pin 3)

//-----------------------------
//Includes
//-----------------------------
#include "Arduino.h"
#include <LiquidCrystal.h>

const int rs = 25, en = 26, d4 = 13, d5 = 12, d6 = 14, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void LCD_init(void){
  lcd.begin(16, 2);
  lcd.clear();

}
#endif