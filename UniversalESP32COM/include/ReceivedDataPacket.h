#ifndef RECEIVED_DATA_PACKET
#define RECEIVED_DATA_PACKET

// Arduino Libraries
#include <Arduino.h>
// Prooject Libraries
#include "ReceivedCommand.h"

constexpr int MAX_COMMANDS = 30;

class ReceivedDataPacket
{
public:
	ReceivedDataPacket();

	bool addCommand(ReceivedCommand &newCommand);

	ReceivedCommand getCommandByIndex(int &index) const;

	ReceivedCommand (&getCommands())[MAX_COMMANDS];

	int getCommandsCount() const;

private:
	ReceivedCommand Commands[MAX_COMMANDS];
	int CommandsCount;
};

#endif // RECEIVED_DATA_PACKET
