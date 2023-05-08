#include "Component.h"

// Constructor
Component::Component() : Id(0), ComponentId(ComponentTypes::Unknown), Description(""), ConnectedPinCount(0) {}

Component::Component(int Id, ComponentTypes ComponentId, String Description) : Id(Id), ComponentId(ComponentId), Description(Description), ConnectedPinCount(0) {}

// Getters and setters
int Component::getId() const { return Id; }

void Component::setId(const int &newId) { Id = newId; }

ComponentTypes Component::getComponentType() const { return ComponentId; }

void Component::setComponentType(const ComponentTypes &newComponentId) { ComponentId = newComponentId; }

// Non-const version
PortPin &Component::getConnectedPinAtIndex(int index)
{
	if (index >= 0 && index < ConnectedPinCount)
	{
		return ConnectedPins[index];
	}
	return ConnectedPins[0];
}

// Const version
const PortPin &Component::getConnectedPinAtIndex(int index) const
{
	if (index >= 0 && index < ConnectedPinCount)
	{
		return ConnectedPins[index];
	}
	return ConnectedPins[0];
}

PortPin (&Component::getConnectedPins())[MAX_ITEMS] { return ConnectedPins; }

int Component::getConnectedPinCount() const { return ConnectedPinCount; }

bool Component::addConnectedPin(PortPin &pin)
{
	if (ConnectedPinCount < MAX_ITEMS)
	{
		ConnectedPins[ConnectedPinCount++] = pin;
		return true;
	}
	return false;
}

const String &Component::getDescription() const { return Description; }

void Component::setDescription(String &newDescription) { Description = newDescription; }
