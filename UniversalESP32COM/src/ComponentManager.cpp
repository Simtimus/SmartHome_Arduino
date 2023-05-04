#include "ComponentManager.h"

ComponentManager::ComponentManager() {}

void ComponentManager::Initialize()
{
	for (int component = 0; component < MAX_ITEMS; component++)
	{
		Component newComponent = Component(component, ComponentManager::ComponentsIds[component], ComponentManager::ComponentsDescription[component]);
		for (int portPin = 0; portPin < MAX_ITEMS; portPin++)
		{
			newComponent.addConnectedPin(PortPin(PortPinsId[component][portPin],
				ComponentManager::PortPinsValue[component][portPin],
				ComponentManager::PortPinsMode[component][portPin],
				ComponentManager::PortPinsValueType[component][portPin]));
			if (PortPinsMode[component][portPin] == PinMode::Read)
				pinMode(PortPinsId[component][portPin], INPUT);
			if (PortPinsMode[component][portPin] == PinMode::Write)
				pinMode(PortPinsId[component][portPin], OUTPUT);
		}
		addComponent(newComponent);
	}
}

// ------------------------------------------------------
// Arduino Pins and Components configuration

ComponentsId ComponentManager::ComponentsIds[MAX_ITEMS] = {
	ComponentsId::LightSensor, //	Component 0
	ComponentsId::Relay,	   //	Component 1
};

String ComponentManager::ComponentsDescription[MAX_ITEMS] = {
	"Located in living room", //	Component 0
	"Controls lamp",		  //	Component 1
};

int ComponentManager::PortPinsId[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		3, // PortPin 0 - Light Sensor
	},
	{
		// Component 1
		4, // PortPin 0 -- Relay
		5, // PortPin 1 -- Button
	},
};

String ComponentManager::PortPinsValue[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		"0", // PortPin 0
	},
	{
		// Component 1
		"0", // PortPin 0
		"0", // PortPin 1
	},
};

PinMode ComponentManager::PortPinsMode[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		PinMode::Read, // PortPin 0
	},
	{
		// Component 1
		PinMode::Write, // PortPin 0
		PinMode::Read,	// PortPin 1
	},
};

ObjectValueType ComponentManager::PortPinsValueType[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		ObjectValueType::Integer, // PortPin 0
	},
	{
		// Component 1
		ObjectValueType::Boolean, // PortPin 0
		ObjectValueType::Boolean, // PortPin 1
	},
};

Component (&ComponentManager::getComponents())[MAX_ITEMS] { return components; }

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

