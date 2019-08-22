#include "Lcd_stream.hpp"

int main()
{
	//configure pins
	Lcd_stream screen('C',2,3,4,5,6,7);
	
	//print "Hello" on default (x:0,y:0) cursor position
	screen << "Hello";

	//set cursor (x:4,y:1)
	screen(4,1);
	
	//then print on it
	screen << "World!";
	
	while(1);

	return 0;
}
