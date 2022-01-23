/*
 * APP.c
 *
 * Created: 1/19/2022 
 * Author : Abdelrhman Elsawy
 */ 

#include "../ECUAL/BTN/Button.h"
#include "../ECUAL/LCD/LCD.h"

BTN_t button1 = { PORTB , PIN2 } ;
	
int main(void)
{
	BTN_u8Init(button1);
	LCD_u8Init();
	uint8_t pressed = 0 ;
	uint8_t u8_PressCounter = 0 ;
	uint8_t arr[] = {"PUSH Counter"};
	LCD_u8SetPosition(0,5);	
	LCD_u8SendString(arr);
	TIMER0_u8PollingDelay_ms(5000);
    while (1) 
    {
		BTN_u8IsPressed ( button1 , &pressed ) ;
		if ( pressed )
			u8_PressCounter ++ ;
		while ( pressed )
			BTN_u8IsPressed ( button1 , &pressed );
		
		LCD_u8ClearScreen();			
		LCD_u8SetPosition(0,0);		
		LCD_u8SendNumber(u8_PressCounter);
		TIMER0_u8PollingDelay_ms(100);	
    }
}

