#include "LCD.h"

extern u8 arr_man[8];
extern u8 arr_deadman[8];


static void LCD_WriteCommand(u8 command)
{
	
	#if LCD_MODE==LCD8_BITMODE

}
static void LCD_WriteData(u8 data)

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
	_delay_ms(2);
}

void LCD_Init (void)
{
	#if LCD_MODE==LCD8_BITMODE
	_delay_ms(50);    
LCD_WriteCommand (0x38);//set 8bit mode , font 5*7
LCD_WriteCommand(0x0c);//cursor off  0x0f,0x0e
LCD_WriteCommand(0x01);//clear screen
_delay_ms(1);
LCD_WriteCommand(0x06);// increase DDRAM address
#elif LCD_MODE==LCD4_BITMODE
_delay_ms(50);
DIO_writePin(RS,LOW);
DIO_writePin(LCD_PIN4,0);
DIO_writePin(EN,HIGH);
LCD_WriteCommand(0x28);// 2 line & font
LCD_WriteCommand(0x0c);// display on /off ,cursor on , blink
LCD_WriteCommand(0x01); // display clear
_delay_ms(1);
LCD_WriteCommand(0x06); // increase , >> right

#endif

     
	
}
void LCD_WriteChar(u8 ch)
{
	 LCD_WriteData(ch); 
}
void LCD_WriteString(u8*str)
{
	u16 i;

	for(i=0;str[i]; i++)//str[i]!='\0'
	{
		LCD_WriteData((u8)str[i]);
	}
}
/*void LCD_WriteNumber(s64 num)
{
	 u8 i=0; 
	 u8 arr[10]={0};
		 if(num<0)
		 {
			 LCD_WriteData('-'); 
			  num=num*(-1);
		 }
		 else if (0==num)
		 {
			  LCD_WriteData('0');
		 }
	 while(num)
	 {
		 arr[i]=num%10;
		 num=num/10;
		i++;
	 }
 for(;i>0;i--)
	 {
		  LCD_WriteData(arr[i-1]+'0');
	 }
	 
}
*/
void LCD_WriteNumber(s64 num)

void LCD_WriteBinary(u8 num)
 { 
	u8 i,flag=0 ;
	  for(i=9;i>0;i--)
	  {
		  if((num>>(i-1)&1))
		  {
			  LCD_WriteNumber(1);
			  flag=1;
		  }
		  else 
		  {
			  if(1==flag)
			    LCD_WriteNumber(0);
		  }
	  }
}
void LCD_WriteHex(u8 num)
{ u8 low=num&0x0f;
	u8 high= num>>4;
	u8 hex [16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	LCD_WriteData(hex[high]);
    LCD_WriteData(hex[low]);	
	

}
void LCD_WriteNumber_4D(u16 num)

void LCD_ShiftCursorRight(u8 line, u8 cell)
{ 
	u8 i;
	if(1==line)
	{
			for(i=0;i<cell;i++)
			{
				LCD_WriteCommand(0x14);	
			}
	}
	else if(2==line)
	{
	  for(i=0;i<cell+0x40;i++)
	  {
		LCD_WriteCommand(0x14);
	  }
	}
}
void LCD_ShiftCursorLeft(void)

void LCD_SetCursor(u8 line, u8 cell)
{
	if(0==line)
	{
		
			LCD_WriteCommand(0x80+cell);
	}
	else if(1==line)
	{
		LCD_WriteCommand(0xc0+cell);
	}
}
void LCD_Displayshift_right(u8 cell)
{ 
	u8 i;
	for(i=0;i<cell;i++)
	{
		LCD_WriteCommand(0x1C);
		
	}
}
void LCD_Displayshift_left(u8 cell)
{
	u8 i;
	for(i=0;i<cell;i++)
	{
		LCD_WriteCommand(0x18);
		
	}
}
u8 str_len(u8*str)
{
	u8 i;
	for(i=0; str[i];i++) //str[i]!='\0'
	{

	}
	return i;
}
void LCD_CursorWriteString(u8 line,u8 cell,u8*str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}

 void LCD_ClearCells(u8 line,u8 cell,u8 num)
{
	LCD_SetCursor(line,cell);
	for (u8 i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
}

void animation (u8 *str )
{
	LCD_SetCursor(1,0);
	LCD_WriteString(str);
	LCD_Displayshift_right(str_len(str)+16);

	LCD_Clear();
	LCD_SetCursor(2,0);
	LCD_WriteString(str);
	LCD_Displayshift_right(str_len(str)+16);
	LCD_Clear();
	LCD_SetCursor(1,0);
}
void animation1 (u8 *str )
{
	u8 i,len=str_len(str),total=len+16;
	LCD_SetCursor1(0,0);
	LCD_Displayshift_left(len);
LCD_WriteString(str);
for(i=0;i<total;i++)
{
	LCD_Displayshift_right(1);
	_delay_ms(300);
}
	LCD_Clear();
	
	LCD_SetCursor1(1,0);
	LCD_Displayshift_left(len);
	LCD_WriteString(str);
	for(i=0;i<total;i++)
	{
		LCD_Displayshift_right(1);
		_delay_ms(300);
	}
	
	LCD_Clear();
}
void Create_Character(u8*Pattern,u8 Location)
{
	u8 i;
	LCD_WriteCommand(0x40+(Location*8));
	for(i=0;i<8;i++)
	{
		LCD_WriteData(Pattern[i]);
	}
	LCD_WriteCommand(0x80);
}
void dead_man(void)
{
	u8 i;
		 Create_Character(arr_man,0);
		 Create_Character(arr_deadman,1);
	 LCD_SetCursor1(1,1);
	  LCD_WriteChar(0);
	   LCD_SetCursor1(1,16);
	   LCD_WriteChar(0);
	 for(i=2;i<=16;i++)
	 {
		    LCD_SetCursor1(1,i);
			LCD_WriteChar(126);
			_delay_ms(300);
			
	 }
	  LCD_SetCursor1(1,16);
	   LCD_WriteChar(0);
}
void playing_man(u8 updown,u8 r_l)
{
	
	//Create_Character(arr_man,0); put out of loop
	
	LCD_SetCursor1(updown,r_l);
	LCD_WriteChar(0);
	if(!DIO_ReadPin(PIND2))
	{
		r_l++;
		if(16==r_l)
		{
			r_l=0;
		}
		while(!DIO_ReadPin(PIND2));
		LCD_Clear();
	}
	if(!DIO_ReadPin(PIND3))
	{
		r_l--;
		if(255==r_l)
		{
			r_l=15;
		}
		while(!DIO_ReadPin(PIND3));
		LCD_Clear();
		
	}
	if(!DIO_ReadPin(PIND4))
	{
		updown++;
		if(2==updown)
		{
			updown=0;
		}
		while(!DIO_ReadPin(PIND4));
		LCD_Clear();
	}
	if(!DIO_ReadPin(PIND5))
	{
		updown--;
		if(255==updown)
		{
			updown=1;
		}
		while(!DIO_ReadPin(PIND5));
		LCD_Clear();
		
	}
	
}/*
void LCD_WriteFloat(f32 Copy_f32Number)
void LCD_WriteFloat(f32 num)