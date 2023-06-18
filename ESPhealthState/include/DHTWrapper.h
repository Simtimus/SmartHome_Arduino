#include "DHT.h"

class DHTWrapper
{
public:
	DHTWrapper();

	void initialize(uint8_t pin, uint8_t type);

	DHT &getDHT();

	String readTemperature();

	String readHumidity();

	String callFunctionBySequence(int Index);

	int getPortPinId() const;
	int getPinCount();

	int MaxPins = 2;

private:
	DHT dht;
	bool initialized;

	int PortPinId = -1;
	int pinCount;
};
