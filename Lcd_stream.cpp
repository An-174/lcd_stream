#include "Lcd_stream.hpp"
extern "C"{
	#include "lcd_reg.h"
}

Lcd_stream::Lcd_stream(uint8_t port,uint8_t rs,uint8_t en,
	uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7)
{
	lcd_init(port,rs,en,d4,d5,d6,d7);
}

void Lcd_stream::prints(const char* s)
{
	lcd_print(s);
}

void Lcd_stream::operator()(uint8_t x,uint8_t y)
{
	set_cursor(x,y);
}

Lcd_stream& operator<<(Lcd_stream& ld,const char *s)
{
	ld.prints(s);
	return ld;
}
