#ifndef COMPONENT_H
#define COMPONENT_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "PortPin.h"
#include "DHTWrapper.h"

constexpr int MAX_ITEMS = 10; // Define a constant for the maximum number of array items

enum class ComponentTypes
{
	Undefined,
	LightSensor,
	Relay,
	Button,
	LedDiode,
	HumiditySensor,
	GasSensor,
	InfraredSensor,
};

class Component
{
public:
	// Constructor
	Component();

	Component(int Id, ComponentTypes ComponentId, String Description);

	// Getters and setters
	int getId() const;
	void setId(const int &newId);

	ComponentTypes getComponentType() const;
	void setComponentType(const ComponentTypes &newComponentId);

	// Non-const version
	PortPin &getConnectedPinAtIndex(int index);

	// Const version
	const PortPin &getConnectedPinAtIndex(int index) const;

	PortPin (&getConnectedPins())[MAX_ITEMS];
	int getConnectedPinCount() const;
	bool addConnectedPin(PortPin &pin);

	const String &getDescription() const;
	void setDescription(String &newDescription);

	int getOtherComponentCount() const;
	
	int getOtherComponentIdAtIndex(int index);

	String getValueByIndexAndSequence(int Index, int Sequence);

	void manageDHTComponent(PortPin &pin);

	String readPinValue(PortPin &pin);

private:
	int Id;
	ComponentTypes ComponentType;
	PortPin ConnectedPins[MAX_ITEMS];
	String Description;
	int ConnectedPinCount;

	int OtherComponentCount;

	DHTWrapper DHTComponents[MAX_ITEMS];
};

#endif // COMPONENT_H
