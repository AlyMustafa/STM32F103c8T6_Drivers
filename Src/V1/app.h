/*
 * app_driver.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Ali Mustafa
 */

#ifndef APP_H_
#define APP_H_
//-----------------------------
//Includes
//-----------------------------
#include "Arduino.h"
#include "mpu6050.h"
//#include "LCD.h"
#include <LiquidCrystal.h>
#include "ultraSonic.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


#define Buzzer 9
void app_init();
char checkBox_hasFalled();
char checkBox_isOpened();
char checkBox_isMoved();
void Battery_Function (void);
//char checkBox_isOpened_AND_Falled();
void app_Start();

#endif