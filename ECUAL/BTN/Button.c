/*
 * Button.c
 *
 * Created: 1/10/2022 12:13:12 AM
 *  Author: Abdelrhman Elsawy
 */ 

#include "../../MCAL/DIO/DIO.h"
#include "Button.h"
#include "BTN_ERR_HANDLE.h"

// function to initialize button 
uint8_t BTN_u8Init ( BTN_t button )
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	// set pin direction to OUTPUT 
	u8ErrorState = DIO_u8SetPinData(button.port,button.pin,INPUTPIN);
	// error checking 
	if ( u8ErrorState == SetPinData_Error )
		u8ErrorState = BTN_Init_Error ;
	return u8ErrorState ;
}

// function to check button pressed or not
uint8_t BTN_u8IsPressed ( BTN_t button , uint8_t * pressed )
{	
	uint8_t u8ErrorState = STD_TYPES_OK;
	uint8_t u8DebounceDetectorHigh = 0 , u8DebounceDetectorLow = 0 , u8BTNState ;
	if (pressed != NULL )
	{
		u8ErrorState = DIO_u8GetPinData(button.port,button.pin,&u8BTNState );
		// error checking 
		if ( u8ErrorState == GetPinData_Error )
		{
			u8ErrorState = BTN_IsPressed_Error ;
		}
		else
		{
			while (1)
			{
				// read until find 5 reads low or five reads high to avoid bouncing 
				DIO_u8GetPinData(button.port,button.pin,&u8BTNState );
				if (u8BTNState==HIGH)
				{
					u8DebounceDetectorHigh++;
					u8DebounceDetectorLow=0;
					u8BTNState = BTN_PRESSED;

				}
				else if (u8BTNState==LOW)
				{
					u8DebounceDetectorHigh=0;
					u8DebounceDetectorLow++;
					u8BTNState = BTN_NOT_PRESSED;
				}
				// confirm the reading if it's repeated 5 times 
				if (u8DebounceDetectorHigh==5 || u8DebounceDetectorLow ==5)
				{
					*pressed = u8BTNState;
					break;
				}
			}
		}
	}
	else
	{
		u8ErrorState = BTN_IsPressed_Error ;
	}
	return u8ErrorState;
}
