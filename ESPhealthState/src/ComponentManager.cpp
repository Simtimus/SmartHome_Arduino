#include "ComponentManager.h"

ComponentManager::ComponentManager() : componentsCount(0) {}

void ComponentManager::Initialize()
{
	for (int component = 0; component < MAX_ITEMS; component++)
	{
		Component newComponent = Component(component, ComponentManager::ComponentsType[component], ComponentManager::ComponentsDescription[component]);
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
		{
			addComponent(newComponent);
		}
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

ComponentTypes ComponentManager::ComponentsType[MAX_ITEMS] = {
	ComponentTypes::HumiditySensor, //	Component 0
	ComponentTypes::GasSensor,		//	Component 1
	ComponentTypes::LedDiode,		//	Component 2
};

String ComponentManager::ComponentsDescription[MAX_ITEMS] = {
	"Living Room & Patio", //	Component 0
	"Kitchen",			   //	Component 1
	"Led Array State",	   //	Component 2
};

// ID musn't be 0
int ComponentManager::PortPinsId[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		4,	// PortPin 0 - DHT22[0]
		4,	// PortPin 1 - DHT22[0]
		13, // PortPin 2 - DHT22[1]
		13, // PortPin 3 - DHT22[1]
	},
	{
		// Component 1
		33, // PortPin 0 -- Gas MQ2
	},
	{
		// Component 2
		27, // PortPin 0 -- Red led
		26, // PortPin 1 -- Yellow Led
		25, // PortPin 2 -- Green Led
	},
};

String ComponentManager::PortPinsValue[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		"0", // PortPin 0
		"0", // PortPin 1
		"0", // PortPin 2
		"0", // PortPin 3
	},
	{
		// Component 1
		"0", // PortPin 0
	},
	{
		// Component 2
		"0", // PortPin 0
		"0", // PortPin 0
		"0", // PortPin 0
	},
};

PinType ComponentManager::PortPinsType[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		PinType::Virtual, // PortPin 0
		PinType::Virtual, // PortPin 1
		PinType::Virtual, // PortPin 2
		PinType::Virtual, // PortPin 3
	},
	{
		// Component 1
		PinType::Real, // PortPin 0
	},
	{
		// Component 2
		PinType::Real, // PortPin 0
		PinType::Real, // PortPin 1
		PinType::Real, // PortPin 2
	},
};

PinMode ComponentManager::PortPinsMode[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		PinMode::Read, // PortPin 0
		PinMode::Read, // PortPin 1
		PinMode::Read, // PortPin 2
		PinMode::Read, // PortPin 3
	},
	{
		// Component 1
		PinMode::Read, // PortPin 0
	},
	{
		// Component 2
		PinMode::Write, // PortPin 0
		PinMode::Write, // PortPin 1
		PinMode::Write, // PortPin 2
	},
};

ObjectValueType ComponentManager::PortPinsValueType[MAX_ITEMS][MAX_ITEMS] = {
	{
		// Component 0
		ObjectValueType::Float, // PortPin 0
		ObjectValueType::Float, // PortPin 1
		ObjectValueType::Float, // PortPin 2
		ObjectValueType::Float, // PortPin 3
	},
	{
		// Component 1
		ObjectValueType::Integer, // PortPin 0
	},
	{
		// Component 2
		ObjectValueType::Boolean, // PortPin 0
		ObjectValueType::Boolean, // PortPin 1
		ObjectValueType::Boolean, // PortPin 2
	},
};
