#include "StdTypes.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "Converter_Interface.h"


#define F_CPU 8000000
#include <util/delay.h>


static c8 message[]="Converter from Omar Abdelbdiea";

static u8 value=0, flag=0;
static u8 BinNum=1;
c8 BinaryArr[8];
s8 BinaryDigits=0;

static u8 string_length(c8 *str)
{
	int i;
	for(i=0; str[i]; i++);

	return i;
}

static void FirstProgram(void)
{
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteString("Convert from");
	LCD_GoTo(1,0);
	LCD_WriteString("1-D   2-B   3-H");
	LCD_GoTo(0,12);
}

static void WriteResult(u8 value, c8 n)
{
	LCD_GoTo(1,2);
	LCD_WriteString("          ");
	LCD_GoTo(1,2);
	if (n=='D')
	{
		LCD_WriteNumber(value);
	}
	else if (n=='B')
	{
		LCD_WriteBinary(value);
	}
	else if (n=='H')
	{
		LCD_WriteHex(value);
	}
	else
	{
		
	}
}

static void WriteDecimal(c8 key)
{
	if (key>='0' && key<='9')
	{
		if (flag==0)
		{
			LCD_GoTo(0,2);
			LCD_WriteString("        ");
			LCD_GoTo(0,2);
			flag=1;
		}
		
		value = value*10 + (key-'0');
		LCD_WriteChar(key);
	}
}

static void WriteBinary(c8 key)
{
	
	if (key=='0' || key=='1')
	{
		if (flag==0)
		{
			LCD_GoTo(0,2);
			LCD_WriteString("         ");
			LCD_GoTo(0,2);
			flag=1;
		}

		BinaryArr[BinaryDigits]=key;
		LCD_WriteChar(key);
		BinaryDigits++;
	}
}

static void WriteHex(c8 key)
{
	if (key>='0' && key<='9')
	{
		if (flag==0)
		{
			LCD_GoTo(0,2);
			LCD_WriteString("        ");
			LCD_GoTo(0,2);
			flag=1;
		}
		value = value*16 + (key-'0');
		LCD_WriteChar(key);
	}
	else if (key>='A' && key <='F')
	{
		if (flag==0)
		{
			LCD_GoTo(0,2);
			LCD_WriteString("        ");
			LCD_GoTo(0,2);
			flag=1;
		}
		value = value*16 + (key-'A'+10);
		LCD_WriteChar(key);
	}

	
}

void Converter_Init(void)
{
	u8 i=0;
	u8 len1=string_length(message);
	
	LCD_GoTo(0,5);
	LCD_WriteString("Hello");
	
	
	while(i<(len1-15))
	{
		LCD_GoTo(1,0);
		LCD_WriteString(message+i);
		i++;
		_delay_ms(300);
	}
	
	
	_delay_ms(1000);
	
	FirstProgram();
}





void Converter_Runnable(void)
{
	c8 k=NO_KEY,system=0;
	static c8 num1=0, num2=0;
	static u8 HexDigits=0;
	static OperationSteps_type option=0;
	
	
	k=KEYPAD_GetKey();
	
	if (k!=NO_KEY)
	{
		
		if (k==DECIMAL && option<=2)
		{
			system='D';
			option++;
		}
		else if (k==BINARY && option<=2)
		{
			system='B';
			option++;
		}
		else if (k==HEX && option<=2)
		{
			system='H';
			option++;
		}
		else if (k=='=' && flag==1)
		{
			BinaryDigits--;
			while(BinaryDigits>=0)
			{
				value += (BinaryArr[BinaryDigits--]-'0')*BinNum;
				BinNum = BinNum<<1;
			}
			WriteResult(value,num2);
			value=0;
			flag=0;
			BinaryDigits=0;
			option=step_3;
			HexDigits=0;
			BinNum=1;
		}
		
		if (option==step_1 && ((k==DECIMAL) || (k==BINARY) || (k==HEX)))
		{
			num1=system;
			LCD_WriteChar(num1);
			LCD_WriteString("to");
		}
		else if (option==step_2 && ((k==DECIMAL) || (k==BINARY) || (k==HEX)) )
		{
			num2=system;
			LCD_WriteChar(num2);
			_delay_ms(500);
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteChar(num1);
			LCD_WriteChar(':');
			LCD_GoTo(1,0);
			LCD_WriteChar(num2);
			LCD_WriteChar(':');
			option++;
		}
		else if (option==step_3)
		{
			
			if(num1=='D' && k!='Z')
			{
				WriteDecimal(k);
			}
			else if (num1=='B' && BinaryDigits<8 && k!='=' && k!='Z')
			{
				WriteBinary(k);
			}
			else if (num1=='H' && HexDigits<2 && k!='=' && k!='Z')
			{
				WriteHex(k);
				HexDigits++;
			}
			else if (k=='Z') //return to initial screen
			{
				FirstProgram();
				option=0;
				value=0;
				HexDigits=0;
				BinaryDigits=0;
			}
		}
		
		
	}
}



