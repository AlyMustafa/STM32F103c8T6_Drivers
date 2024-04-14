
/*
 * mpu6050_driver.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Ali Mustafa
 */

#ifndef MPU6050_H_
#define MPU6050_H_

//-----------------------------
//Includes
//-----------------------------
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Arduino.h"

//-----------------------------
void mpu_init(void);
void  mpu_Update(void);
float mpu_get_Pitch();
float mpu_get_Yaw();
float mpu_get_Roll();
#endif