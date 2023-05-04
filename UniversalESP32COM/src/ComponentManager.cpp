#include "ComponentManager.h"

ComponentManager::ComponentManager() {}

void ComponentManager::Initialize()
{
	for (int component = 0; component < sizeof(ComponentsIds); component++)
	{
		Component newComponent = Component(component, ComponentsIds[component], ComponentsDescription[component]);
		for (int portPin = 0; portPin < sizeof(PortPinsMode[component]); portPin++)
		{
			newComponent.addConnectedPin(PortPin(PortPinsId[component][portPin], PortPinsValue[component][portPin], PortPinsMode[component][portPin], PortPinsValueType[component][portPin]));
			if (PortPinsMode[component][portPin] == PinMode::Read)
				pinMode(PortPinsId[component][portPin], INPUT);
			if (PortPinsMode[component][portPin] == PinMode::Write)
				pinMode(PortPinsId[component][portPin], OUTPUT);
		}
		addComponent(newComponent);
	}
}

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

// ------------------------------------------------------
// Arduino Pins and Components configuration

ComponentsId ComponentsIds[MAX_ITEMS] = {
	ComponentsId::LightSensor, //	Component 0
	ComponentsId::Relay,	   //	Component 1
};

String ComponentsDescription[MAX_ITEMS] = {
	"Located in living room", //	Component 0
	"Controls lamp",		  //	Component 1
};

int PortPinsId[MAX_ITEMS][MAX_ITEMS] = {
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

String PortPinsValue[MAX_ITEMS][MAX_ITEMS] = {
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

PinMode PortPinsMode[MAX_ITEMS][MAX_ITEMS] = {
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

ObjectValueType PortPinsValueType[MAX_ITEMS][MAX_ITEMS] = {
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
