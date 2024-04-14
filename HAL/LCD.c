/*************************************************************************/
/* Author        : Ali Mustafa                                   		 	*/
/* Project       : STM32F103C8T6_Drivers  	                          	   	*/
/* File          : LCD.c 			                             			*/
/* Date          : Jan 28, 2024                                         	*/
/* Version       : V1                                                   	*/
/* GitHub        :             		     									*/
/*************************************************************************/

#include "LCD.h"

void delay(unsigned int time)
{
	unsigned int i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void LCD_GPIO_init(void)
{
	GPIO_config_t pin_Cfg;
	pin_Cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pin_Cfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	//******************************************///Control Pins///**************************************//
	pin_Cfg.GPIO_PinNumber = RS;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = RW;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = EN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);
	//********************************************///DATA Pins///**************************************//
#if LCD_MODE == EIGHT_BIT_MODE

	pin_Cfg.GPIO_PinNumber = D0_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D1_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D2_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D3_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

#endif

	pin_Cfg.GPIO_PinNumber = D4_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D5_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D6_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	pin_Cfg.GPIO_PinNumber = D7_PIN;
	MCAL_GPIO_Init(lcd_port, &pin_Cfg);

	delay(20); //finish initialization
}

void LCD_init()
{
	delay(20);
	LCD_GPIO_init();
	delay(15);
	MCAL_GPIO_WritePin(lcd_control_port, EN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(lcd_control_port, RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(lcd_control_port, RW, GPIO_PIN_RESET);

#if LCD_MODE == EIGHT_BIT_MODE
	LCD_Clear_Screen();
	LCD_send_command(LCD_FUNCTION_8BIT_2LINES);
	LCD_send_command(LCD_ENTRY_MODE);
	LCD_send_command(LCD_BEGIN_AT_FIRST_ROW);
	//LCD_send_command(LCD_DISP_ON_CURSOR);

#endif
#if LCD_MODE == FOUR_BIT_MODE
	MCAL_GPIO_WritePin(lcd_port, D4_PIN, (LCD_FUNCTION_4BIT_2LINES&0x10));
	MCAL_GPIO_WritePin(lcd_port, D5_PIN, (LCD_FUNCTION_4BIT_2LINES&0x20));
	MCAL_GPIO_WritePin(lcd_port, D6_PIN, (LCD_FUNCTION_4BIT_2LINES&0x40));
	MCAL_GPIO_WritePin(lcd_port, D7_PIN, (LCD_FUNCTION_4BIT_2LINES&0x80));
	LCD_Kick_Enable();
	delay(1);
	LCD_send_command(LCD_FUNCTION_4BIT_2LINES);
#endif
	LCD_Clear_Screen();
	LCD_send_command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_send_command(LCD_ENTRY_MODE);
	LCD_send_command(LCD_DISP_ON_CURSOR);
}

void LCD_Kick_Enable(void)
{
	MCAL_GPIO_WritePin(lcd_control_port, EN, GPIO_PIN_SET);
	delay(50);
	MCAL_GPIO_WritePin(lcd_control_port, EN, GPIO_PIN_RESET);
}

void LCD_send_command(unsigned char command)
{
	MCAL_GPIO_WritePin(lcd_control_port, RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(lcd_control_port, RW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(lcd_control_port, EN, GPIO_PIN_RESET);

#if LCD_MODE == EIGHT_BIT_MODE
	MCAL_GPIO_WritePin(lcd_port , D0_PIN , (command&0x01) );
	MCAL_GPIO_WritePin(lcd_port , D1_PIN , (command&0x02) );
	MCAL_GPIO_WritePin(lcd_port , D2_PIN , (command&0x04) );
	MCAL_GPIO_WritePin(lcd_port , D3_PIN , (command&0x08) );
	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (command&0x10) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (command&0x20) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (command&0x40) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (command&0x80) );
	delay(1);
	LCD_Kick_Enable();


#endif

#if LCD_MODE == FOUR_BIT_MODE
	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (command&0x10) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (command&0x20) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (command&0x40) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (command&0x80) );
	delay(1);
	LCD_Kick_Enable();
	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (command&0x01) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (command&0x02) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (command&0x04) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (command&0x08) );
	delay(1);
	LCD_Kick_Enable();
#endif
}

void LCD_send_character(unsigned char character)
{
	MCAL_GPIO_WritePin(lcd_control_port, RS, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(lcd_control_port, RW, GPIO_PIN_RESET);

#if LCD_MODE == EIGHT_BIT_MODE

	MCAL_GPIO_WritePin(lcd_port , D0_PIN , (character&0x01) );
	MCAL_GPIO_WritePin(lcd_port , D1_PIN , (character&0x02) );
	MCAL_GPIO_WritePin(lcd_port , D2_PIN , (character&0x04) );
	MCAL_GPIO_WritePin(lcd_port , D3_PIN , (character&0x08) );
	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (character&0x10) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (character&0x20) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (character&0x40) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (character&0x80) );
	delay(1);
	LCD_Kick_Enable();

#endif

#if LCD_MODE == FOUR_BIT_MODE

	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (character&0x10) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (character&0x20) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (character&0x40) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (character&0x80) );
	delay(1);
	LCD_Kick_Enable();

	MCAL_GPIO_WritePin(lcd_port , D4_PIN , (character&0x01) );
	MCAL_GPIO_WritePin(lcd_port , D5_PIN , (character&0x02) );
	MCAL_GPIO_WritePin(lcd_port , D6_PIN , (character&0x04) );
	MCAL_GPIO_WritePin(lcd_port , D7_PIN , (character&0x08) );
	delay(1);
	LCD_Kick_Enable();

#endif
}

void LCD_send_string( const char* string)
{
	int i=0; // to tell how much the display fills
	while(*string > 0){
		i++;
		LCD_send_character(*string++);
		if(i == 16)
			LCD_set_cursor(1,0);
		if (i >= 32)
		{
			LCD_set_cursor(0,0);
			i=0;
		}
	}
}

void LCD_Clear_Screen(){
	LCD_send_command(LCD_CLEAR_SCREEN);
}
/**=============================================
 * @Fn				- LCD_Set_Cursor
 * @brief 			- Sets the location of the cursor
 * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
 * @param [in] 	- column: Selects the column number of the displayed character (1...16)
 * @param [out] 	- None
 * @retval 		- None
 * Note			- None
 */
void LCD_set_cursor(unsigned char row , unsigned char column ){
	if (row == 0)
	{
		if(column >= 0 && column < 16)
			LCD_send_command(LCD_BEGIN_AT_FIRST_ROW + column);
	}
	if (row == 1)
	{
		if(column >= 0 && column < 16)
			LCD_send_command(LCD_BEGIN_AT_SECOND_ROW + column);
	}
}


void LCD_send_Num (uint32_t NUM){
	uint32_t string[7];
	sprintf (string, "%d" ,NUM);
	LCD_send_string(string);


}
