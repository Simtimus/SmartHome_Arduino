#include "Component.h"

// Constructor
Component::Component() : Id(0), ComponentId(ComponentsId::Unknown), Description(""), ConnectedPinCount(0) {}

Component::Component(int Id, ComponentsId ComponentId, String Description) : Id(Id), ComponentId(ComponentId), Description(Description), ConnectedPinCount(0) {}

// Getters and setters
int Component::getId() const { return Id; }
void Component::setId(const int &newId) { Id = newId; }

ComponentsId Component::getComponentId() const { return ComponentId; }
void Component::setComponentId(ComponentsId newComponentId) { ComponentId = newComponentId; }

const PortPin &Component::getConnectedPinAtIndex(int index) const
{
	if (index >= 0 && index < ConnectedPinCount)
	{
		return ConnectedPins[index];
	}
	// You should handle the case when the index is out of bounds.
	// For this example, we will return the first element.
	return ConnectedPins[0];
}

PortPin *Component::getConnectedPins() { return ConnectedPins; }
int Component::getConnectedPinCount() const { return ConnectedPinCount; }

bool Component::addConnectedPin(const PortPin &pin)
{
	if (ConnectedPinCount < MAX_ITEMS)
	{
		ConnectedPins[ConnectedPinCount++] = pin;
		return true;
	}
	return false;
}

String Component::getDescription() const { return Description; }
void Component::setDescription(const String &newDescription) { Description = newDescription; }
