#ifndef __LCD_H
#define __LCD_H

#include "main.h"
#include "LCD_Config.h"

//private defines
#if _LCD_USE_FREERTOS==0
#include "cmsis_os.h"
#endif


//function prototypes
void lcd_init (void);   // initialize lcd
void send_to_lcd (char data, int rs);  //send to lcd
void lcd_send_cmd (char cmd);  // send command to the lcd
void lcd_send_data (char data);  // send data to the lcd
void lcd_send_string (char *str);  // send string to the lcd
void lcd_clear (void);
void lcd_String_xy (char row, char pos, char *str);

#endif /* __LCD_H*/
