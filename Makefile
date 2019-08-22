MCU=atmega8535
CPU=2000000UL
MCU_FLAG=-mmcu=$(MCU)
CPU_FLAG=-DF_CPU=$(CPU)
SUPPORT_FLAGS=-g -c -Wall -Os
CC=avr-gcc -std=c11
CPP=avr-g++ -std=c++11

main.cpp.hex : main.cpp.out
	avr-objdump -h -S build/main.cpp.out > build/main.lst
	avr-size build/main.cpp.out
	avr-objcopy -O ihex -R .flash build/main.cpp.out build/main.cpp.hex
	
main.cpp.out : main.cpp.o
	$(CC) $(MCU_FLAG)  -Wl,-Map,build/main.map -o build/main.cpp.out build/main.cpp.o build/lcd_reg.c.o build/Lcd_stream.cpp.o

main.cpp.o : main.cpp
	$(CC) $(SUPPORT_FLAGS) $(MCU_FLAG) $(CPU_FLAG) lcd_reg.c -o build/lcd_reg.c.o
	$(CPP) $(SUPPORT_FLAGS) $(MCU_FLAG) $(CPU_FLAG) Lcd_stream.cpp -o build/Lcd_stream.cpp.o
	$(CPP) $(SUPPORT_FLAGS) $(MCU_FLAG) $(CPU_FLAG) main.cpp -o build/main.cpp.o


