#ifndef LCD_STREAM_
#define LCD_STRAEM_
#include <avr/io.h>

class Lcd_stream{
	void prints(const char* s);
public:
	Lcd_stream(uint8_t port,uint8_t rs,uint8_t en,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
	void operator()(uint8_t x,uint8_t y);
	friend Lcd_stream& operator<<(Lcd_stream &ld,const char *s);
};

#endif
