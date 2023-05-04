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
	void setComponentId(ComponentsId newComponentId);

	const PortPin &getConnectedPinAtIndex(int index) const;

	PortPin *getConnectedPins();
	int getConnectedPinCount() const;
	bool addConnectedPin(const PortPin &pin);

	String getDescription() const;
	void setDescription(const String &newDescription);

private:
	int Id;
	ComponentsId ComponentId;
	PortPin ConnectedPins[MAX_ITEMS];
	String Description;		// Max length 32 characters
	int ConnectedPinCount;
};

#endif // COMPONENT_H
