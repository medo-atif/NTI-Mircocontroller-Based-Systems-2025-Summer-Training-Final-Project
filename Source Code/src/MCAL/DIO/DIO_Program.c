#include <stdint.h>
#include "../../../inc/MCAL/DIO/DIO_Interface.h"
#include "../../../inc/BitMath.h"
#include "../../../inc/MCAL/NTI_Atmega32Register.h"

void mDIO_ChangeDirectionForPin(uint8_t GroupName , uint8_t PinNumber , uint8_t DirectionState)
{
	if(PinNumber>= Pin0 && PinNumber <=Pin7)
	{
		if (DirectionState==DIO_Output)
		{
			switch(GroupName)
			{
			case GroupA: SetBit(DDRA_Reg,PinNumber);break;
			case GroupB: SetBit(DDRB_Reg,PinNumber);break;
			case GroupC: SetBit(DDRC_Reg,PinNumber);break;
			case GroupD: SetBit(DDRD_Reg,PinNumber);break;
			default :  // GroupName Outof Rang
				break;
			}
		}
		else if (DirectionState==DIO_Input)
		{
			switch(GroupName)
			{
			case GroupA: ClearBit(DDRA_Reg ,PinNumber);break;
			case GroupB: ClearBit(DDRB_Reg,PinNumber);break;
			case GroupC: ClearBit(DDRC_Reg,PinNumber);break;
			case GroupD: ClearBit(DDRD_Reg,PinNumber);break;
			default :  // GroupName Outof Rang
				break;
			}
		}
		else
		{
			//DirectionState NotVaild
		}
	}
	else
	{
		// Pin Number Outof Range
	}
}

void mDIO_WriteValueForPin(uint8_t GroupName ,  uint8_t PinNumber , uint8_t OutputType)
{
	//	Task2
	if(PinNumber>= Pin0 && PinNumber <=Pin7)
	{
		if (OutputType==DIO_High)
		{
			switch(GroupName)
			{
			case GroupA: SetBit(PORTA_Reg,PinNumber);break;
			case GroupB: SetBit(PORTB_Reg,PinNumber);break;
			case GroupC: SetBit(PORTC_Reg,PinNumber);break;
			case GroupD: SetBit(PORTD_Reg,PinNumber);break;
			default :  // GroupName Outof Rang
				break;
			}
		}
		else if (OutputType==DIO_Low)
		{
			switch(GroupName)
			{
			case GroupA: ClearBit(PORTA_Reg ,PinNumber);break;
			case GroupB: ClearBit(PORTB_Reg,PinNumber);break;
			case GroupC: ClearBit(PORTC_Reg,PinNumber);break;
			case GroupD: ClearBit(PORTD_Reg,PinNumber);break;
			default :  // GroupName Out of Rang
				break;
			}
		}
		else
		{
			// NotVaild Output Type
		}
	}
	else
	{
		// Pin Number Out of Range
	}
}

uint8_t mDIO_ReadValueFromPin(uint8_t  GroupName, uint8_t PinNumber)
{
	// Task3
	uint8_t InputValue = 0;

	if(PinNumber>= Pin0 && PinNumber <=Pin7)
	{
		switch(GroupName)
		{
		case GroupA: InputValue = GetBit(PINA_Reg,PinNumber);break;
		case GroupB: InputValue = GetBit(PINB_Reg,PinNumber);break;
		case GroupC: InputValue = GetBit(PINC_Reg,PinNumber);break;
		case GroupD: InputValue = GetBit(PIND_Reg,PinNumber);break;
		default :  // GroupName Outof Rang
			break;
		}	
	}
	else
	{
		// Pin Number Out of Range
	}

	return  InputValue;
}

void mDIO_ChangeDirectionforGroup(uint8_t GroupName , uint8_t Direction)
{
	//Task 4
	if (Direction>=0x00 && Direction<=0xFF)
	{
		switch(GroupName)
		{
		case GroupA: DDRA_Reg = Direction;break;
		case GroupB: DDRB_Reg = Direction;break;
		case GroupC: DDRC_Reg = Direction;break;
		case GroupD: DDRD_Reg = Direction;break;
		default :  // GroupName Outof Rang
			break;
		}
	}
	else
	{
		//DirectionState NotVaild
	}
}

void mDIO_WriteValueForGroup(uint8_t GroupName ,  uint8_t OutputValue)
{
	if(OutputValue>=0x00 && OutputValue<=0xFF)
	{
		switch(GroupName)
		{
		case GroupA: PORTA_Reg = OutputValue;break;
		case GroupB: PORTB_Reg = OutputValue;break;
		case GroupC: PORTC_Reg = OutputValue;break;
		case GroupD: PORTD_Reg = OutputValue;break;
		default: // GroupName Not Vaild
			break ;
		}
	}
	else
	{
		// Output value out of Range
	}
}

uint8_t mDIO_ReadValueFromGroup(uint8_t  GroupName)
{
	// Task 5
	uint8_t InputValue = 0;

	switch(GroupName)
	{
	case GroupA: InputValue = PINA_Reg;break;
	case GroupB: InputValue = PINB_Reg;break;
	case GroupC: InputValue = PINC_Reg;break;
	case GroupD: InputValue = PIND_Reg;break;
	default :  // GroupName Outof Rang
		break;
	}	

	return  InputValue;
}
