#include "EepromString.h"

EepromString::EepromString(uint16_t startAddress, uint16_t maxLength)
	: _startAddress(startAddress), _maxLength(maxLength)
{
	EEPROM.begin(4096); // Adjust the size to match your EEPROM size
}

bool EepromString::isDefault()
{
	uint16_t length = EEPROM.read(_startAddress);
	length = min(length, _maxLength);

	for (uint8_t i = 1; i <= length; i++)
	{
		if (EEPROM.read(_startAddress + i) == 0xFF)
			return true;
	}
	return false;
}

void EepromString::write(const String &str)
{
	uint16_t length = str.length() + 1; // +1 for the null-terminator
	length = min(length, _maxLength);

	EEPROM.write(_startAddress, length);
	for (uint16_t i = 0; i < length; i++)
	{
		EEPROM.write(_startAddress + 1 + i, str[i]);
	}
	EEPROM.commit();
}

String EepromString::read()
{
	uint16_t length = EEPROM.read(_startAddress);
	length = min(length, _maxLength);

	String result;
	for (uint16_t i = 0; i < length; i++)
	{
		result += (char)EEPROM.read(_startAddress + 1 + i);
	}
	return result;
}

String EepromString::readGuid()
{
	uint16_t length = EEPROM.read(_startAddress);
	length = min(length, _maxLength);

	String result;
	for (uint16_t i = 0; i < length; i++)
	{
		if (EEPROM.read(_startAddress + 1 + i) == 0xFF)
			return Board::DefaultGuid;
		else
			result += (char)EEPROM.read(_startAddress + 1 + i);
	}
	return result;
}
