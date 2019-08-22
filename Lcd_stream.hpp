/*Written by An Priyatna

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
 */

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
