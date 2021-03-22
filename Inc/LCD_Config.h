#ifndef __LCD_CONFIG_H
#define	__LCD_CONFIG_H

#define _LCD_USE_FREERTOS 1
#define _LCD_COLS         16
#define _LCD_ROWS         2


#define RS_GPIO_Port GPIOA
#define RS_Pin GPIO_PIN_4

#define RW_GPIO_Port GPIOA
#define RW_Pin GPIO_PIN_6

#define EN_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_7

#define D4_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_4

#define D5_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_0

#define D6_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_1

#define D7_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_2

#endif
