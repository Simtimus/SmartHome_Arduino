#include "DHTWrapper.h"

DHTWrapper::DHTWrapper() : dht(0, 0, 0), initialized(false), pinCount(0) {}

void DHTWrapper::initialize(uint8_t pin, uint8_t type)
{
	PortPinId = pin;
	dht = DHT(pin, type);
	dht.begin();
	initialized = true;
}

DHT &DHTWrapper::getDHT()
{
	if (!initialized)
	{
		Serial.println("<ERROR> DHT has not been initialized yet");
	}
	return dht;
}

String DHTWrapper::readTemperature()
{
	if (!initialized)
	{
		return "<ERROR> DHT has not been initialized yet";
	}
	return String(dht.readTemperature(false, false));
}

String DHTWrapper::readHumidity()
{
	if (!initialized)
	{
		return "<ERROR> DHT has not been initialized yet";
	}
	return String(dht.readHumidity(false));
}

String DHTWrapper::callFunctionBySequence(int Index)
{
	switch (Index)
	{
	case 0:
		return readTemperature();

	case 1:
		return readHumidity();

	default:
		return "Index " + String(Index) + " at CallFunction";
	}
}

int DHTWrapper::getPortPinId() const { return PortPinId; }

int DHTWrapper::getPinCount()
{
	if (pinCount < MaxPins)
	{
		return pinCount++;
	}
	else
	{
		return pinCount;
	}
}