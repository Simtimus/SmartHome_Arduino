#ifndef RECEIVED_COMMAND
#define RECEIVED_COMMAND

// Arduino Libraries
#include <Arduino.h>
// Prooject Libraries
// ...

enum CommandAction
{
	SetId,
	SetValue
};

class ReceivedCommand
{
public:
	ReceivedCommand();
	ReceivedCommand(String value, CommandAction action, int componentId, int pinId);

	void setValue(const String &newValue);
	String getValue() const;

	void setAction(const CommandAction &newAction);
	CommandAction getAction() const;

	void setComponentId(const int &newComponentId);
	int getComponentId() const;

	void setPinId(const int &newPinId);
	int getPinId() const;

private:
	String Value;
	CommandAction Action;
	int ComponentId = -1;
	int PinId = -1;
};

#endif // RECEIVED_COMMAND
