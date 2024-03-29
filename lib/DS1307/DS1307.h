/*
  DS1307.h - Arduino library support for the DS1307 I2C Real-Time Clock
  Copyright (C)2016 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to easily interface and use the DS1307 RTC with
  the Arduino without needing the Wire library.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef DS1307_h
#define DS1307_h

#if defined(__AVR__)
	#include "Arduino.h"
	#include "hardware/avr/HW_AVR_defines.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
	#include "hardware/pic32/HW_PIC32_defines.h"
#elif defined(__arm__)
	#include "Arduino.h"
	#include "hardware/arm/HW_ARM_defines.h"
#endif

#define DS1307_ADDR_R	0xD1
#define DS1307_ADDR_W	0xD0
#define DS1307_ADDR		0x68

#define FORMAT_SHORT	1
#define FORMAT_LONG		2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define SQW_RATE_1		0
#define SQW_RATE_4K		1
#define SQW_RATE_8K		2
#define SQW_RATE_32K	3

class Time
{
public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;

	Time();

	bool operator==(const Time& t)
	{
		return hour == t.hour && min == t.min && sec == t.sec &&
			   date == t.date && mon == t.mon && year == t.year && dow == t.dow;
	}

	bool operator!=(const Time& t)
	{
		return !(hour == t.hour && min == t.min && sec == t.sec &&
			   date == t.date && mon == t.mon && year == t.year && dow == t.dow);
	}
};

class DS1307_RAM
{
public:
	byte	cell[56];

		DS1307_RAM();
};

class DS1307
{
	public:
		DS1307(uint8_t data_pin, uint8_t sclk_pin);
		void	begin();
		Time	getTime();
		void	setTime(uint8_t hour, uint8_t min, uint8_t sec);
		void	setDate(uint8_t date, uint8_t mon, uint16_t year);
		void	setDOW();
		void	setDOW(uint8_t dow);

		char	*getTimeStr(uint8_t format=FORMAT_LONG);
		char	*getDateStr(uint8_t slformat=FORMAT_LONG, uint8_t eformat=FORMAT_LITTLEENDIAN, char divider='.');
		char	*getDOWStr(uint8_t format=FORMAT_LONG);
		char	*getMonthStr(uint8_t format=FORMAT_LONG);
		long	getUnixTime(Time t);

		void	halt(bool value);
		void	setOutput(bool enable);
		void	enableSQW(bool enable);
		void	setSQWRate(int rate);

		void		writeBuffer(DS1307_RAM r);
		DS1307_RAM	readBuffer();
		void		poke(uint8_t addr, uint8_t value);
		uint8_t		peek(uint8_t addr);

	private:
		uint8_t _scl_pin;
		uint8_t _sda_pin;
		uint8_t _burstArray[8];
		boolean	_use_hw;

		void	_sendStart(byte addr);
		void	_sendStop();
		void	_sendAck();
		void	_sendNack();
		void	_waitForAck();
		uint8_t	_readByte();
		void	_writeByte(uint8_t value);
		void	_burstRead();
		uint8_t	_readRegister(uint8_t reg);
		void 	_writeRegister(uint8_t reg, uint8_t value);
		uint8_t	_decode(uint8_t value);
		uint8_t	_decodeH(uint8_t value);
		uint8_t	_decodeY(uint8_t value);
		uint8_t	_encode(uint8_t vaule);
#if defined(__arm__)
		Twi		*twi;
#endif
};
#endif
