#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <Arduino.h>
#include "Component.h"
#include "PortPin.h"

class ComponentManager
{
public:
	// Constructor
	ComponentManager();

	void Initialize();

	Component *getComponents();
	int getComponentsCount() const;
	bool addComponent(const Component &newComponent);

	ComponentsId ComponentsIds[MAX_ITEMS];
	String ComponentsDescription[MAX_ITEMS];

	PinMode PortPinsMode[MAX_ITEMS][MAX_ITEMS];
	ObjectValueType PortPinsValueType[MAX_ITEMS][MAX_ITEMS];

private:
	Component components[MAX_ITEMS];
	int componentsCount;
};

#endif // COMPONENT_MANAGER_H
