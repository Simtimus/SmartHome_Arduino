#ifndef EEPROM_STRING_H
#define EEPROM_STRING_H

// Arduino Libraries
#include <Arduino.h>
#include <EEPROM.h>
// Project Libraries
#include "Board.h"

class EepromString
{
public:
	EepromString(uint16_t startAddress, uint16_t maxLength);
	bool isDefault();
	void write(const String &str);
	String read();
	String readGuid();

private:
	uint16_t _startAddress;
	uint16_t _maxLength;
};

#endif // EEPROM_STRING_H
