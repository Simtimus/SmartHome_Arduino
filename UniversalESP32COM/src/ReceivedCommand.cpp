#include "ReceivedCommand.h"

ReceivedCommand::ReceivedCommand() {}

ReceivedCommand::ReceivedCommand(String value, CommandAction action, int componentId, int pinId):
	Value(value), Action(action), ComponentId(componentId), PinId(pinId) {}

void ReceivedCommand::setValue(const String &newValue)
{
	Value = newValue;
}
String ReceivedCommand::getValue() const
{
	return Value;
}

void ReceivedCommand::setAction(const CommandAction &newAction)
{
	Action = newAction;
}
CommandAction ReceivedCommand::getAction() const
{
	return Action;
}

void ReceivedCommand::setComponentId(const int &newComponentId)
{
	ComponentId = newComponentId;
}
int ReceivedCommand::getComponentId() const
{
	return ComponentId;
}

void ReceivedCommand::setPinId(const int &newPinId)
{
	PinId = newPinId;
}
int ReceivedCommand::getPinId() const
{
	return PinId;
}