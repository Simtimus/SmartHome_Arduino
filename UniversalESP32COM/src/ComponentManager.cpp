#include "ComponentManager.h"

ComponentManager::ComponentManager() : componentsCount(0) {}

void ComponentManager::Initialize()
{
	for (int component = 0; component < MAX_ITEMS; component++)
	{
		Component newComponent = Component(component, ComponentManager::ComponentsIds[component], ComponentManager::ComponentsDescription[component]);
		for (int portPin = 0; portPin < MAX_ITEMS; portPin++)
		{
			// Take care
			if (PortPinsId[component][portPin] == 0)
				break;

			PortPin newPortPin(PortPinsId[component][portPin],
				ComponentManager::PortPinsValue[component][portPin],
				ComponentManager::PortPinsType[component][portPin],
				ComponentManager::PortPinsMode[component][portPin],
				ComponentManager::PortPinsValueType[component][portPin],
				component);

			newComponent.addConnectedPin(newPortPin);

			if (PortPinsMode[component][portPin] == PinMode::Read)
				pinMode(PortPinsId[component][portPin], INPUT);
			if (PortPinsMode[component][portPin] == PinMode::Write)
				pinMode(PortPinsId[component][portPin], OUTPUT);
		}
		if (newComponent.getConnectedPinCount() != 0)
			addComponent(newComponent);
	}
};

Component (&ComponentManager::getComponents())[MAX_ITEMS] { return components; }

int ComponentManager::getComponentsCount() const { return componentsCount; }

bool ComponentManager::addComponent(Component &newComponent)
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

ComponentTypes ComponentManager::ComponentsIds[MAX_ITEMS] = {
	ComponentTypes::LightSensor,	//	Component 0
	ComponentTypes::Relay,			//	Component 1
	ComponentTypes::HumiditySensor, //	Component 1
};

String ComponentManager::ComponentsDescription[MAX_ITEMS] = {
	"Room light",					 //	Component 0
	"Controls room lamp",			 //	Component 1
	"Room temperature and humidity", //	Component 2
};

// ID musn't be 0
int ComponentManager::PortPinsId[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		18, // PortPin 0 - Light Sensor
	},
	{
		// Component 1
		4, // PortPin 0 -- Relay
		5, // PortPin 1 -- Button
	},
	{
		// Component 2
		15, // PortPin 0 -- DHT22[0]
		15, // PortPin 1 -- DHT22[0]
	},
};

String ComponentManager::PortPinsValue[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		"751", // PortPin 0
	},
	{
		// Component 1
		"0", // PortPin 0
		"0", // PortPin 1
	},
	{
		// Component 2
		"0", // PortPin 0
		"0", // PortPin 0
	},
};

PinType ComponentManager::PortPinsType[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		PinType::Real, // PortPin 0
	},
	{
		// Component 1
		PinType::Real, // PortPin 0
		PinType::Real, // PortPin 1
	},
	{
		// Component 2
		PinType::Virtual, // PortPin 0
		PinType::Virtual, // PortPin 0
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
	{
		// Component 2
		PinMode::Read, // PortPin 0
		PinMode::Read, // PortPin 0
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
	{
		// Component 2
		ObjectValueType::Float, // PortPin 0
		ObjectValueType::Float, // PortPin 1
	},
};
