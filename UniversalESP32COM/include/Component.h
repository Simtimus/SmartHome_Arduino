#ifndef COMPONENT_H
#define COMPONENT_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "PortPin.h"

constexpr int MAX_ITEMS = 10; // Define a constant for the maximum number of array items

enum class ComponentsId
{
	Unknown,
	LightSensor,
	Relay,
};

class Component
{
public:
	// Constructor
	Component();

	Component(int Id, ComponentsId ComponentId, String Description);

	// Getters and setters
	int getId() const;
	void setId(const int &newId);

	ComponentsId getComponentId() const;
	void setComponentId(const ComponentsId &newComponentId);

	const PortPin &getConnectedPinAtIndex(int index) const;

	PortPin (&getConnectedPins())[MAX_ITEMS];
	int getConnectedPinCount() const;
	bool addConnectedPin(const PortPin &pin);

	const String &getDescription() const;
	void setDescription(String &newDescription);

private:
	int Id;
	ComponentsId ComponentId;
	PortPin ConnectedPins[MAX_ITEMS];
	String Description;
	int ConnectedPinCount;
};

#endif // COMPONENT_H
