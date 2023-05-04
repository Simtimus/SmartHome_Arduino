#include "ComponentManager.h"

ComponentManager::ComponentManager() {}

void ComponentManager::Initialize()
{
	for (int component = 0; component < sizeof(ComponentsIds); component++)
	{
		Component newComponent = Component(component, ComponentsIds[component], ComponentsDescription[component]);
		for (int portPin = 0; portPin < sizeof(PortPinsMode[component]); portPin++)
		{
			newComponent.addConnectedPin(PortPin(portPin, PortPinsMode[component][portPin], PortPinsValueType[component][portPin]));
		}
		addComponent(newComponent);
	}
}

Component *ComponentManager::getComponents() { return components; }
int ComponentManager::getComponentsCount() const { return componentsCount; }

bool ComponentManager::addComponent(const Component &newComponent)
{
	if (componentsCount < MAX_ITEMS)
	{
		components[componentsCount++] = newComponent;
		return true;
	}
	return false;
}

// Arduino Pins and Components configuration

ComponentsId ComponentsIds[MAX_ITEMS] = {
	ComponentsId::LightSensor, //	Component 0
	ComponentsId::Relay,	   //	Component 1
};

String ComponentsDescription[MAX_ITEMS] = {
	"Located in living room", //	Component 0
	"Controls lamp",		  //	Component 1
};

PinMode PortPinsMode[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		PinMode::Read, // PortPin 0
	},
	{
		// Component 1
		PinMode::Read, // PortPin 0
	},
};

ObjectValueType PortPinsValueType[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		ObjectValueType::Integer, // PortPin 0
	},
	{
		// Component 1
		ObjectValueType::Boolean, // PortPin 0
	},
};
