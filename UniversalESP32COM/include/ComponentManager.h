#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "Component.h"
#include "PortPin.h"

class ComponentManager
{
public:
	// Constructor
	ComponentManager();

	void Initialize();

	Component (&getComponents())[MAX_ITEMS];
	int getComponentsCount() const;
	bool addComponent(const Component &newComponent);

	ComponentsId ComponentsIds[MAX_ITEMS];
	String ComponentsDescription[MAX_ITEMS];

	int PortPinsId[MAX_ITEMS][MAX_ITEMS];
	String PortPinsValue[MAX_ITEMS][MAX_ITEMS];
	PinMode PortPinsMode[MAX_ITEMS][MAX_ITEMS];
	ObjectValueType PortPinsValueType[MAX_ITEMS][MAX_ITEMS];

private:
	Component components[MAX_ITEMS];
	int componentsCount;
};

#endif // COMPONENT_MANAGER_H
