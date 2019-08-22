#include "lcd_reg.h"
#include <util/delay.h>

//store any port-pins configured here
static uint8_t dat_pins[7];
static volatile uint8_t *DATA_OUT;
static uint8_t RS;
static uint8_t EN;

void send(uint8_t val)
{
	send_4line(val >> 4);
	send_4line(val);
}

void command(uint8_t val)	//command mode
{
	*DATA_OUT &= ~RS;	//rs on lcd pin needs to be low
	send(val);
}

void write(uint8_t val)	//write mode
{
	*DATA_OUT |= RS;	//rs on lcd pin needs to be high
	send(val);
}


void enablePin_pulse(void)
{
	*DATA_OUT &= ~EN;	//mask by its own value
	_delay_us(20);
	*DATA_OUT |= EN;
	_delay_us(20);		//enable pulse must be more than 450ns
	*DATA_OUT &= ~EN;
	_delay_us(100); 	//commands need to be more than 37us
	//see table 6 of page 24 for details
}

void send_4line(uint8_t ch)
{
	*DATA_OUT &= (RS | EN);	//mask for RS and EN bits
	for(uint8_t i=3;i<=6;++i)
		if((ch>>(i-3)) & 0x01)	//if bit == 1 
			*DATA_OUT |= (1<<dat_pins[i]);	//set 1 to the particular pin
	enablePin_pulse();
}

void configure_pins(uint8_t port,uint8_t rs,uint8_t en,
	uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7)
{
	dat_pins[0] = port;
	dat_pins[1] = rs;
	dat_pins[2] = en;
	dat_pins[3] = d4;
	dat_pins[4] = d5;
	dat_pins[5] = d6;
	dat_pins[6] = d7;

	activate_port(dat_pins);
}

void activate_port(uint8_t* pins)
{
	uint8_t pin_num = 0;
	
	RS |= (1<<dat_pins[1]);	//for latter use on functions
	EN |= (1<<dat_pins[2]);

	for(uint8_t i=1;i<=6;++i)
	{
		pin_num = (1<<pins[i]);
		switch(pins[0])
		{
			//note: make macro variable
			case 'A':case 'a': 
				DATA_OUT = (volatile uint8_t*) &PORTA;
				DDRA |= pin_num; 
			break;
			case 'B':case 'b': 
				DATA_OUT = (volatile uint8_t*) &PORTB;
				DDRB |= pin_num; 
			break;
			case 'C':case 'c': 
				DATA_OUT = (volatile uint8_t*) &PORTC;
				DDRC |= pin_num; 
			break;
			case 'D':case 'd': 
				DATA_OUT = (volatile uint8_t*) &PORTD;
				DDRD |= pin_num;
		}
	}
}

void lcd_init(uint8_t port,uint8_t rs,uint8_t en,
	uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7)
{		
	configure_pins(port,rs,en,d4,d5,d6,d7);
	
	//according to datasheet, we need to wait more than 4.5ms after Vcc rises to 2.7v
	_delay_us(50000);
	
	//to begin the command, RW, EN, and RS pins need to be low
	//based on our schematic, RW is directly connected to ground
	//that automatically has the low state
	*DATA_OUT &= ~(RS | EN);

	//since on the schematic, the 4-line connection is used
	//we set the lcd mode into 4-bit
	//the steps are according to hitachi HD44780 flow-chart, see page 45 - 46
	//starting with 8-bit mode
	send_4line(0x03);
	_delay_us(4100);	//wait for 4.1ms

	//next step
	send_4line(0x03);
	_delay_us(4100);	//wait for 4100us

	//finally
	send_4line(0x03);
	_delay_us(150);

	send_4line(0x02); //for 4-bit mode
	
	//set # lines, font size, etc.	
	command(FUNCTION_SET | DISP_2LINES);	
	_delay_us(4200);	//waitmore than 4.1ms
	
	//turn the display on
	command(DISP_CONTROL | DISP_ON);

	//clear the display
	clear_disp();

	//set the entry mode
	command(ENTRY_MODESET | ENTRYLEFT);}

void clear_disp(void)
{
	//clear entire display and set DDRAM to 0 on address counter
	command(CLEAR_DISPLAY);
	_delay_ms(2);
}

void lcd_print(const char *s)
{
	while(*s)
		write(*s++);
}

void set_cursor(uint8_t x, uint8_t y)
{
	const uint8_t ddram_address[4] = {0x00, 0x40, 0x14, 0x54};
	command(DDRAM_ADDRESS | (x + ddram_address[y]));
}
	
