
#include "lcd.h"


void lcd_init (void)
{

	//intialise lcd pins since we have not intialised it before.
	GPIO_InitTypeDef gpio;
	gpio.Mode=GPIO_MODE_OUTPUT_OD;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	gpio.Pin = RS_Pin;
	HAL_GPIO_Init(RS_GPIO_Port,&gpio);

	gpio.Pin = RW_Pin;
	HAL_GPIO_Init(RW_GPIO_Port,&gpio);

	gpio.Pin = EN_Pin;
	HAL_GPIO_Init(EN_GPIO_Port,&gpio);

	gpio.Pin = D4_Pin;
	HAL_GPIO_Init(D4_GPIO_Port,&gpio);

	gpio.Pin = D5_Pin;
	HAL_GPIO_Init(D5_GPIO_Port,&gpio);

	gpio.Pin = D6_Pin;
	HAL_GPIO_Init(D6_GPIO_Port,&gpio);

	gpio.Pin = D7_Pin;
	HAL_GPIO_Init(D7_GPIO_Port,&gpio);

	HAL_Delay(1);

	// 4 bit initialisation
	lcd_send_cmd (0x33);
	HAL_Delay(1);
	lcd_send_cmd (0x32);
	HAL_Delay(1);
	lcd_send_cmd (0x28);
	HAL_Delay(1);

  // dislay initialisation
	lcd_send_cmd (0x0C);  // Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x01); //clear display
}

void send_to_lcd (char data, int rs)
{
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);  // rs = 1 for data, rs=0 for command
    /* write the data to the respective pin */
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (data & 0x08));
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (data & 0x04));
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (data & 0x02));
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (data & 0x01));
    /* Toggle EN PIN to send the data*/

    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
    HAL_Delay(1);
}


void lcd_send_cmd (char cmd)
{
    char commandtosend;

    /* send upper nibble first */
    commandtosend = (cmd>>4);
    send_to_lcd(commandtosend,0);  // RS must be 0 while sending command

    /* send Lower Nibble */
    commandtosend = ((cmd)&0x0f);
	send_to_lcd(commandtosend, 0);
}

void lcd_send_data (char data)
{
	char datatosend;

	// send higher nibble
	datatosend = (data>>4);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	// send Lower nibble
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_send_string (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)		// Send each char of string till the NULL
	{
		lcd_send_data (str[i]);
	}
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(1);
	lcd_send_cmd(0x80);		// cursor at home position
	HAL_Delay(1);
}

void lcd_String_xy (char row, char pos, char *str)// Send string to LCD with xy position
{
	if (row == 0 && pos<16)
	lcd_send_cmd((pos & 0x0F)|0x80);	// Command of first row and required position<16
	else if (row == 1 && pos<16)
	lcd_send_cmd((pos & 0x0F)|0xC0);	// Command of first row and required position<16
	lcd_send_string(str);		// Call LCD string function *
}
