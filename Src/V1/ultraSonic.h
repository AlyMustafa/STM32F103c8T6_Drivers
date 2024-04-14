/*
 * ultraSonic_driver.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Ali Mustafa
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

//-----------------------------
//Includes
//-----------------------------
#include "Arduino.h"

#define SOUND_VELOCITY 0.034    //define sound velocity in cm/uS

void UltraSonic_init(void);
float Ultrasonic_get_distance(void);


#endif