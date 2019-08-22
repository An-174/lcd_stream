#ifndef LCD_REG_HEADER_
#define LCD_REG_HEADER_
#include <avr/io.h>

//parameters taken from hd44780u datasheet
//table 6 on page 24
#define FUNCTION_SET 	0x20
#define DISP_2LINES 		0x08
#define CLEAR_DISPLAY	0x01
#define DISP_CONTROL		0x08
#define DISP_ON			0x04

#define ENTRY_MODESET	0x04
#define ENTRYLEFT 		0x02

#define DDRAM_ADDRESS	0x80

void send(uint8_t val);
void command(uint8_t val);
void write(uint8_t val);
void enablePin_pulse(void);
void send_4line(uint8_t ch);
void lcd_init(uint8_t port,uint8_t rs,uint8_t en,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
void clear_disp(void);
void lcd_print(const char *s);
void configure_pins(uint8_t port,uint8_t rs,uint8_t en,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
void activate_port(uint8_t* pins);
void set_cursor(uint8_t x,uint8_t y);

#endif
