#ifndef SENDING_SERVICE_H
#define SENDING_SERVICE_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "UdpCommunication.h"
#include "ClientData.h"
#include "ComponentManager.h"
#include "Board.h"
#include "Component.h"
#include "EepromString.h"
#include "JsonConverter.h"

class SendingService
{
public:
	SendingService(UdpCommunication &UdpComm, EepromString &Eeprom, ComponentManager &CompManager, ClientData &Client, Board &Board);

	void runService();

	void transmitBoardInfo();
	void transmitFullDevice();
	void transmitSingleComponent(int &componentIndex, bool (&changedPortPins)[MAX_ITEMS]);
	void transmitSinglePortPin(int &componentIndex, bool (&changedPortPins)[MAX_ITEMS]);

	void updateChangedPinValues(bool (&changedPortPins)[MAX_ITEMS][MAX_ITEMS], int (&changedPortPinsCount)[MAX_ITEMS]);

	void selectTransmissionMode(bool (&changedPortPins)[MAX_ITEMS][MAX_ITEMS], int (&changedPortPinsCount)[MAX_ITEMS]);

private:
	bool wakedUp = true;
	UdpCommunication udpComm;
	EepromString eeprom;
	ComponentManager compManager;
	ClientData client;
	Board board;
};

#endif // SENDING_SERVICE_H
