/*
 * SerialUART.h
 *
 * Created: 2/12/2017 5:41:25 PM
 * Author : Nayanda Haberrty <nayanda1@outlook.com>
 */ 
 
 #ifndef UARTSERIAL2560_H_
#define UARTSERIAL2560_H_
#define __DELAY_BACKWARD_COMPATIBLE__

#endif /* UARTSERIAL2560_H_ */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

class SerialUART{
	private:

	static const uint8_t RX_ENABLE = 4, TX_ENABLE = 3, U_STOP_BIT = 3, UCSZ0 = 1, UCSZ1 = 2, RX_FLAG = 7, UDR_READY = 5;

	protected:

	//register address
	volatile uint8_t *ubrrl, *ubrrh, *ucsra, *ucsrb, *ucsrc, *udr;

	//class variable
	uint16_t ubrrVal;
	unsigned long timeOneBit;

	/**
	 * \brief 
	 * 
	 * \param 
	 * 
	 * \return bool
	 */
	bool timeout(void);

	/**
	 * \brief 
	 * 
	 * \param serial
	 * 
	 * \return bool
	 */
	static bool timeout(SerialUART *serial);

	/**
	 * \brief 
	 * 
	 * \param serial
	 * \param baud
	 * \param ubrrl
	 * \param ubrrh
	 * \param ucsra
	 * \param ucsrb
	 * \param ucsrc
	 * \param udr
	 * 
	 * \return void
	 */
	static void init(SerialUART *serial, unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh, uint8_t *ucsra, uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr);
	
	/**
	 * \brief 
	 * 
	 * \param ucsra
	 * \param udr
	 * 
	 * \return char
	 */
	static char getChar(volatile uint8_t *ucsra, volatile uint8_t *udr);
	
	/**
	 * \brief 
	 * 
	 * \param ucsra
	 * \param udr
	 * \param character
	 * 
	 * \return void
	 */
	static void putChar(volatile uint8_t *ucsra, volatile uint8_t *udr, const char character);
	
	/**
	 * \brief 
	 * 
	 * \param serial
	 * \param string
	 * 
	 * \return void
	 */
	static void print(SerialUART *serial, char *string);
	
	/**
	 * \brief 
	 * 
	 * \param serial
	 * \param string
	 * \param size
	 * 
	 * \return int
	 */
	static int scan(SerialUART *serial, char *string, unsigned int size);
	
	/**
	 * \brief 
	 * 
	 * \param ucsra
	 * 
	 * \return bool
	 */
	static bool available(volatile uint8_t *ucsra);
	
	/**
	 * \brief 
	 * 
	 * \param ucsra
	 * \param udr
	 * 
	 * \return void
	 */
	static void flush(volatile uint8_t *ucsra, volatile uint8_t *udr);

	public:
	
	/**
	 * \brief 
	 * 
	 * \param ubrrl
	 * \param ubrrh
	 * \param ucsra
	 * \param ucsrb
	 * \param ucsrc
	 * \param udr
	 * 
	 * \return 
	 */
	SerialUART(uint8_t *ubrrl, uint8_t *ubrrh, uint8_t *ucsra, uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr);
	
	/**
	 * \brief 
	 * 
	 * \param baud
	 * \param ubrrl
	 * \param ubrrh
	 * \param ucsra
	 * \param ucsrb
	 * \param ucsrc
	 * \param udr
	 * 
	 * \return 
	 */
	SerialUART(unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh, uint8_t *ucsra, uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr);
	
	/**
	 * \brief 
	 * 
	 * \param 
	 * 
	 * \return 
	 */
	~SerialUART(void);

	/**
	 * \brief 
	 * 
	 * \param baud
	 * \param ubrrl
	 * \param ubrrh
	 * \param ucsra
	 * \param ucsrb
	 * \param ucsrc
	 * \param udr
	 * 
	 * \return void
	 */
	void init(unsigned long baud, uint8_t *ubrrl, uint8_t *ubrrh, uint8_t *ucsra, uint8_t *ucsrb, uint8_t *ucsrc, uint8_t *udr);
	
	/**
	 * \brief 
	 * 
	 * \param 
	 * 
	 * \return char
	 */
	char getChar(void);
	
	/**
	 * \brief 
	 * 
	 * \param character
	 * 
	 * \return void
	 */
	void putChar(char character);
	
	/**
	 * \brief 
	 * 
	 * \param string
	 * 
	 * \return void
	 */
	void print(const char *string);
	
	/**
	 * \brief 
	 * 
	 * \param string
	 * \param size
	 * 
	 * \return int
	 */
	int scan(char *string, unsigned int size);
	
	/**
	 * \brief 
	 * 
	 * \param 
	 * 
	 * \return bool
	 */
	bool available(void);
	
	/**
	 * \brief 
	 * 
	 * \param 
	 * 
	 * \return void
	 */
	void flush(void);

};