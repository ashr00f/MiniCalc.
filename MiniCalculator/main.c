
//#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD.h"
#include "KeyPad.h"


int main(void)
{
	DIO_Init();
	LCD_Init();
	
	u8 i,operation_flag=0,operation_number=0,temp,two_operations_flag=0,continue_flag=0,first_operation_flag=0;
	u8 arr[16]={0},j=0;
f32 n1=0,n2=0;
 f32 res=0;
    
    while (1) 
    {
		i=KEYPAD_GetEntry();
		if(i!=NO_KEY)
		{
			/*multi operation protection*/
			if(i=='+'||i=='/'||i=='-'||i=='*')
			{
				two_operations_flag++;
			}	
			if(i!='='&&i!='c')
			{
				
				arr[j++]=i;
				if((arr[0]=='+'||arr[0]=='/'||arr[0]=='-'||arr[0]=='*')&&continue_flag==0)
				{
					LCD_WriteFloat(n1);
					continue_flag=1 ;
				}
			else if(continue_flag==0)
			    {
				n1=0;
				operation_flag=0;
			    }
				LCD_WriteChar(i);
			}		
			 if(i=='='||two_operations_flag==2)
			{
				LCD_ClearCells(1,0,15);
				LCD_SetCursor(1,0);
				for(u8 k=0;k<j;k++)
				{
					if(arr[k]>='0'&&arr[k]<='9'&&operation_flag==0)
					{
						n1=n1*10+(arr[k]-'0');
						//LCD_WriteNumber(n1);
					}
					else if(arr[k]>='0'&&arr[k]<='9'&&operation_flag==1)
					{
						n2=n2*10+(arr[k]-'0');
						//LCD_WriteNumber(n2);
					}
					else
					{
					switch(arr[k])	
					{
						case '+':
						operation_number=0;
						break;
						case '-':
						operation_number=1;
						break;
						case '*':
						operation_number=2;
						break;
						case '/':
						operation_number=3;
						break;
					}
					operation_flag=1;
					if (!first_operation_flag)
					{
						temp=operation_number;
						first_operation_flag=1;
					}
					
					}
				
				}
				switch(temp)
				{
					case 0:
					res=n1+n2;
					LCD_WriteFloat(res);
					break;
					case 1:
					res=n1-n2;
					LCD_WriteFloat(res);
					break;
					case 2:
					res=n1*n2;
					LCD_WriteFloat(res);
					break;
					case 3:
					if(n2!=0)
					{
					res=n1/n2;
					LCD_WriteFloat(res);	
					}
					else
					LCD_WriteString("error");
					break;
				}
				n1=res;
				n2=0;
				j=0;
				continue_flag=0;
				two_operations_flag=0;
				first_operation_flag=0;
				LCD_ClearCells(0,0,15);
				LCD_SetCursor(0,0);
			}
			else if(i=='c')
			{
				LCD_Clear();
				for(u8 k=0;k<j;k++)
				{
					arr[k]=0;
				}
				j=0;
				n1=0;
				n2=0;
				res=0;
				operation_flag=0;
				continue_flag=0;
				operation_number=0;
				first_operation_flag=0;
				two_operations_flag=0;
			}
			//while
		}
    }
}

