/*
 * SerialUART.cpp
 *
 * Created: 2/12/2017 5:41:25 PM
 * Author : Nayanda Haberrty <nayanda1@outlook.com>
 */

#include <avr/io.h>
#include <util/delay.h>
#include "SerialUART.h"

SerialUART::SerialUART(bool def, uint8_t *ubrrl, uint8_t *ubrrh,  uint8_t *ucsra,  uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr){
	if(def)
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
	serial->setBaud(baud);
	serial->ubrrl = ubrrl;
	serial->ubrrh = ubrrh;
	serial->ucsra = ucsra;
	serial->ucsrb = ucsrb;
	serial->ucsrc = ucsrc;
	serial->udr = udr;
	 // set 8 bit data and 2 bit stop bit
	*(serial->ucsrc) = ((1<<U_STOP_BIT)|(1<<UCSZ0)|(1<<UCSZ1));
	serial->enableSerial();
}

void SerialUART::enableRX(void){
	*(this->ucsrb) |= (1<<RX_ENABLE);
}

void SerialUART::enableTX(void){
	*(this->ucsrb) |= (1<<TX_ENABLE);
}

void SerialUART::enableSerial(void){
	*(this->ucsrb) = ((1<<RX_ENABLE)|(1<<TX_ENABLE));
}

void SerialUART::disableRX(void){
	*(this->ucsrb) |= (0<<RX_ENABLE);
}

void SerialUART::disableTX(void){
	*(this->ucsrb) |= (0<<TX_ENABLE);
}

void SerialUART::disableSerial(void){
	*(this->ucsrb) = ((0<<RX_ENABLE)|(0<<TX_ENABLE));
}
void SerialUART::setBaud(unsigned long baud){
	setBaud(this, baud);
}

void SerialUART::setBaud(SerialUART *serial, unsigned long baud){
	serial->timeOneBit = 1000000/baud;
	serial->ubrrVal = F_CPU/16/baud-1;
	setUBRR(serial);
}

unsigned long SerialUART::getBaud(void){
	return 1000000 * timeOneBit;
}

void SerialUART::setUBRR(unsigned int ubrr){
	this->ubrrVal = ubrr;
	setUBRR(this);
}

void SerialUART::setUBRR(SerialUART *serial){
	*(serial->ubrrh) = serial->ubrrVal>>7;
	*(serial->ubrrl) = serial->ubrrVal;
}

unsigned int SerialUART::getUBRR(void){
	return this->ubrrVal;
}

void SerialUART::setUCSR(uint8_t ucsra, uint8_t ucsrb, uint8_t ucsrc){
	setUCSR(this, ucsra, ucsrb, ucsrc);
}

void SerialUART::setUCSR(SerialUART *serial, uint8_t ucsra, uint8_t ucsrb, uint8_t ucsrc){
	*(serial->ucsra) = ucsra;
	*(serial->ucsrb) = ucsrb;
	*(serial->ucsrc) = ucsrc;
}

uint8_t SerialUART::getUCSR(uint8_t n){
	return getUCSR(this, n);
}

uint8_t SerialUART::getUCSR(SerialUART *serial, uint8_t n){
	switch(n){
		case 0:
		return *(serial->ucsra);
		
		case 1:
		return *(serial->ucsrb);
		
		case 2:
		return *(serial->ucsrc);
	}
	return 0x00;
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

int SerialUART::scan(char *str, unsigned int size){
	return SerialUART::scan(this, str, size);
}

int SerialUART::scan(SerialUART *uart, char *str, unsigned int size){
	unsigned int i = 0, t = 0;
	while(!t && i < size){
		*str = uart->getChar();
		t = uart->timeout();
		str++; i++;
	}
	return i;
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