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

	static ComponentsId ComponentsIds[MAX_ITEMS];
	static String ComponentsDescription[MAX_ITEMS];

	static int PortPinsId[MAX_ITEMS][MAX_ITEMS];
	static String PortPinsValue[MAX_ITEMS][MAX_ITEMS];
	static PinMode PortPinsMode[MAX_ITEMS][MAX_ITEMS];
	static ObjectValueType PortPinsValueType[MAX_ITEMS][MAX_ITEMS];

	Component (&getComponents())[MAX_ITEMS];
	int getComponentsCount() const;
	bool addComponent(Component &newComponent);

private:
	Component components[MAX_ITEMS];
	int componentsCount;
};

#endif // COMPONENT_MANAGER_H
