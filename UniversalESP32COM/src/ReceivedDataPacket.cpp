#include "ReceivedDataPacket.h"

ReceivedDataPacket::ReceivedDataPacket() {}

bool ReceivedDataPacket::addCommand(ReceivedCommand &newCommand)
{
	if (CommandsCount < MAX_COMMANDS)
	{
		Commands[CommandsCount++] = newCommand;
		return true;
	}
	return false;
}

ReceivedCommand ReceivedDataPacket::getCommandByIndex(int &index) const
{
	if (index >= 0 && index < CommandsCount)
	{
		return Commands[index];
	}
	// You should handle the case when the index is out of bounds.
	// For this example, we will return the first element.
	return Commands[0];
}

ReceivedCommand (&ReceivedDataPacket::getCommands())[MAX_COMMANDS]
{
	return Commands;
}

int ReceivedDataPacket::getCommandsCount() const
{
	return CommandsCount;
}