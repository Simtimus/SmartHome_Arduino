#ifndef RECEIVING_SERVICE_H
#define RECEIVING_SERVICE_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "JsonConverter.h"
#include "UdpCommunication.h"
#include "EepromString.h"
#include "ReceivedDataPacket.h"
#include "Board.h"
#include "Component.h"


class ReceivingService
{
public:
	ReceivingService(UdpCommunication &UdpComm, EepromString &Eeprom, Board &newBoard);

	void runService();

	void processCommands(ReceivedDataPacket &dataPacket);

	void updateBoardPinsState();

private:
	UdpCommunication udpComm;
	EepromString eeprom;
	Board board;
	bool wakedUp;
};

#endif // RECEIVING_SERVICE_H
