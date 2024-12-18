#include "Component.h"

// Constructor
Component::Component() : Id(0), ComponentType(ComponentTypes::Undefined), Description(""), ConnectedPinCount(0), OtherComponentCount(0) {}

Component::Component(int Id, ComponentTypes ComponentType, String Description) : Id(Id), ComponentType(ComponentType), Description(Description), ConnectedPinCount(0), OtherComponentCount(0) {}

// Getters and setters
int Component::getId() const { return Id; }

void Component::setId(const int &newId) { Id = newId; }

ComponentTypes Component::getComponentType() const { return ComponentType; }

void Component::setComponentType(const ComponentTypes &newComponentType) { ComponentType = newComponentType; }

// Non-const version
PortPin &Component::getConnectedPinAtIndex(int index)
{
	if (index >= 0 && index < ConnectedPinCount)
	{
		return ConnectedPins[index];
	}
	return ConnectedPins[0];
}

// Non-const version
PortPin &Component::getConnectedPinById(int pinId)
{
	for (int index = 0; index < ConnectedPinCount; index++)
	{
		if (ConnectedPins[index].getId() == pinId)
		{
			return ConnectedPins[index];
		}
	}
	return ConnectedPins[0];
}

// Const version
const PortPin &Component::getConnectedPinAtIndex(int index) const
{
	if (index >= 0 && index < ConnectedPinCount)
	{
		return ConnectedPins[index];
	}
	return ConnectedPins[0];
}

// Const version
const PortPin &Component::getConnectedPinById(int pinId) const
{
	for (int index = 0; index < ConnectedPinCount; index++)
	{
		if (ConnectedPins[index].getId() == pinId)
		{
			return ConnectedPins[index];
		}
	}
	return ConnectedPins[0];
}

PortPin (&Component::getConnectedPins())[MAX_ITEMS] { return ConnectedPins; }

int Component::getConnectedPinCount() const { return ConnectedPinCount; }

bool Component::addConnectedPin(PortPin &pin)
{
	if (ConnectedPinCount < MAX_ITEMS)
	{
		if (ComponentType == ComponentTypes::HumiditySensor)
		{
			manageDHTComponent(pin);
		}
		if (pin.getType() == PinType::Virtual)
		{
			int newId = ConnectedPinCount + 100;
			pin.setId(newId);

			// Serial.print("<DEBUG> Pin ID: ");
			// Serial.print(pin.getId());
			// Serial.print(" | Pin OthCmp ID: ");
			// Serial.print(pin.getOtherComponentId());
			// Serial.print(" | Pin OthCmp Seq: ");
			// Serial.println(pin.getOtherComponentSequence());
		}
		ConnectedPins[ConnectedPinCount++] = pin;
		
		return true;
	}
	return false;
}

const String &Component::getDescription() const { return Description; }

void Component::setDescription(String &newDescription) { Description = newDescription; }

int Component::getOtherComponentCount() const { return OtherComponentCount; }

int Component::getOtherComponentIdAtIndex(int index)
{
	if (index >= 0 && index < OtherComponentCount)
	{
		switch (ComponentType)
		{
		case ComponentTypes::HumiditySensor:
			return DHTComponents[index].getPortPinId();
		
		default:
			return -1;
		}
	}
	else
	{
		switch (ComponentType)
		{
		case ComponentTypes::HumiditySensor:
			return DHTComponents[0].getPortPinId();

		default:
			return -1;
		}
	}
}

String Component::getValueByIndexAndSequence(int Index, int Sequence)
{
	switch (ComponentType)
	{
	case ComponentTypes::HumiditySensor:
		return DHTComponents[Index].callFunctionBySequence(Sequence);
	
	default:
		return "<ERROR> Other Component out of reach";
	}
}

void Component::manageDHTComponent(PortPin &pin)
{
	// Serial.print("<DEBUG> OthCmp Count = ");
	// Serial.print(OtherComponentCount);
	// Serial.print(" | PinId: ");
	// Serial.println(pin.getId());

	if (OtherComponentCount == 0)
	{
		DHTComponents[OtherComponentCount].initialize(pin.getId(), DHT22);
		pin.setOtherComponentId(DHTComponents[OtherComponentCount].getPortPinId());
		pin.setOtherComponentSequence(DHTComponents[OtherComponentCount++].getPinCount());
	}
	else
	{
		int index = -1;
		int pinOtherComponentId = pin.getId();
		for (int i = 0; i < OtherComponentCount; i++)
		{
			if (DHTComponents[i].getPortPinId() == pinOtherComponentId)
			{
				index = i;
				break;
			}
		}

		// Serial.print("<DEBUG> DHT List Index: ");
		// Serial.println(index);

		if (index != -1)
		{
			pin.setOtherComponentId(DHTComponents[index].getPortPinId());
			pin.setOtherComponentSequence(DHTComponents[index].getPinCount());
		}
		else
		{
			DHTComponents[OtherComponentCount].initialize(pin.getId(), DHT22);
			pin.setOtherComponentId(DHTComponents[OtherComponentCount].getPortPinId());
			pin.setOtherComponentSequence(DHTComponents[OtherComponentCount++].getPinCount());
		}
	}
}

String Component::readPinValue(PortPin &pin)
{
	if (pin.getType() == PinType::Real)
	{
		if (pin.getValueType() == ObjectValueType::Boolean)
			return String(digitalRead(pin.getId()));
		else
			return String(analogRead(pin.getId()));
	}
	else
	{
		int pinId = pin.getId();
		int pinOthCmpId = pin.getOtherComponentId();
		if (ComponentType == ComponentTypes::HumiditySensor)
		{
			int index = -1;
			for (int i = 0; i < OtherComponentCount; i++)
			{
				// Serial.print("<DEBUG> OthCmp Id: ");
				// Serial.print(getOtherComponentIdAtIndex(i));
				// Serial.print(" | PinId: ");
				// Serial.print(pinId);
				// Serial.print(" | Pin OthCmp Id: ");
				// Serial.println(pinOthCmpId);

				if (getOtherComponentIdAtIndex(i) == pinOthCmpId)
				{
					index = i;
					break;
				}
				// delay(500);
			}

			if (index != -1)
			{
				// Serial.print("<DEBUG> Index: ");
				// Serial.print(index);
				// Serial.print(" | Virtual ID: ");
				// Serial.print(pin.getId());
				// Serial.print(" | Comp ID: ");
				// Serial.print(pin.getOtherComponentId());
				// Serial.print(" | Seq: ");
				// Serial.print(pin.getOtherComponentSequence());
				// Serial.print(" | Value: ");
				// Serial.println(getValueByIndexAndSequence(index, pin.getOtherComponentSequence()));

				return getValueByIndexAndSequence(index, pin.getOtherComponentSequence());
			}
			else
			{
				return "<ERROR> Virtual pin out of reach";
			}
		}
		else
		{

			return "<ERROR> No such ComponentType: " + int(ComponentType);
		}
	}
}
