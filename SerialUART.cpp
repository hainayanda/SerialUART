/*
 * SerialUART.cpp
 *
 * Created: 2/12/2017 5:41:25 PM
 * Author : Nayanda Haberrty <nayanda1@outlook.com>
 */

#include <avr/io.h>
#include <util/delay.h>
#include "SerialUART2560.h"

SerialUART::SerialUART(uint8_t *ubrrl, uint8_t *ubrrh,  uint8_t *ucsra,  uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr){
	init(9600L, ubrrl, ubrrh, ucsra, ucsrb, ucsrc, udr);
}

SerialUART::SerialUART(unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh,  uint8_t *ucsra,  uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr){
	init(baud, ubrrl, ubrrh, ucsra, ucsrb, ucsrc, udr);
}

SerialUART::~SerialUART(void){
	flush();
	*ubrrh = 0x00;
	*ubrrl = 0x00;
	*ucsra = 0x00;
	*ucsrb = 0x00;
	*ucsrc = 0x00;
}

void SerialUART::init(unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh,  uint8_t *ucsra,  uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr){
	SerialUART::init(this, baud, ubrrl, ubrrh, ucsra, ucsrb, ucsrc, udr);
}

void SerialUART::init(SerialUART *serial, unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh,  uint8_t *ucsra, uint8_t *ucsrb, uint8_t *ucsrc,  uint8_t *udr){
	serial->timeOneBit = 1000000/baud;
	serial->ubrrVal = F_CPU/16/baud-1;
	serial->ubrrl = ubrrl;
	serial->ubrrh = ubrrh;
	serial->ucsra = ucsra;
	serial->ucsrb = ucsrb;
	serial->ucsrc = ucsrc;
	serial->udr = udr;
	*(serial->ubrrh) = serial->ubrrVal>>7;
	*(serial->ubrrl) = serial->ubrrVal;
	 //enable TX0 and RX0
	*(serial->ucsrb) = ((1<<RX_ENABLE)|(1<<TX_ENABLE));
	 // set 8 bit data and 2 bit stop bit
	*(serial->ucsrc) = ((1<<U_STOP_BIT)|(1<<UCSZ0)|(1<<UCSZ1));
}

char SerialUART::getChar(void){
	return SerialUART::getChar(ucsra, udr);
}

char SerialUART::getChar(volatile uint8_t *ucsra, volatile uint8_t *udr){
	while (!(*ucsra & (1<<RX_FLAG)));
	return *udr;
}

void SerialUART::putChar(const char character){
	SerialUART::putChar(character);
}

void SerialUART::putChar(volatile uint8_t *ucsra, volatile uint8_t *udr, const char character){
	while (!(*ucsra & (1<<UDR_READY)));
	*udr = character;
}

void SerialUART::print(const char *string){
	SerialUART::print(string);
}

void SerialUART::print(SerialUART *uart, char *string){
	while(*string != '\0'){
		uart->putChar(*string);
		string++;
	}
}

void SerialUART::scan(char *str, unsigned int size){
	SerialUART::scan(this, str, size);
}

void SerialUART::scan(SerialUART *uart, char *str, unsigned int size){
	unsigned int i = 0, t = 0;
	while(!t && i < size){
		*str = uart->getChar();
		t = uart->timeout();
		str++; i++;
	}
}

bool SerialUART::available(void){
	return SerialUART::available(ucsra);
}

bool SerialUART::available(volatile uint8_t *ucsra){
	if (*ucsra & (1<<RX_FLAG)) return true;
	else return false;
}

bool SerialUART::timeout(void){
	return SerialUART::timeout(this);
}

bool SerialUART::timeout(SerialUART *uart){
	int time = 0;
	while (!uart->available() && time < 1000){
		unsigned int i= 0;
		while(i < uart->timeOneBit){
			_delay_us(1);
			i++;
		}
		time++;
	} if (time < 1000) return false;
	else return true;
}

void SerialUART::flush(void){
	SerialUART::flush(ucsra, udr);
}

void SerialUART::flush(volatile uint8_t *ucsra, volatile uint8_t *udr){
	char dummy;
	while (*ucsra & (1<<RX_FLAG)) dummy = *udr;
	return;
}