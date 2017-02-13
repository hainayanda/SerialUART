# SerialUART
UART universal library for ATmel Microcontroller

## Synopsis

This is simple universal library for UART Serial communication using Atmel Microcontroller. This code is written in C++ and compatible with Atmel Studio 7. it using most common protocol in UART Serial, feel free to edit the code when you needed

## Code Example

Using the code is very simple. Just create the object and pass the address of UART register you want (UBRR, UCSR and UDR) and you are good to go.

//create default object with baud rate 9600 bps at serial pin 0

SerialUART serial(&UBRR0L, &UBRR0H, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0);

//create object with custom baud rate, in this case are 19200 bps at serial pin 1

SerialUART otherSerial(19200L, &UBRR1L, &UBRR1H, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1);

//send char

serial.putChar('a');

//send string

serial.print("Hello World");

//get char

char character = serial.getChar();

//get string

char[100] string;
serial.scan(string, 100);

//flush UDR

serial.flush();

## Motivation

This is my personal library to use serial pin for Atmel Microcontroller. I think its a good thing if I share it for someone who need it
