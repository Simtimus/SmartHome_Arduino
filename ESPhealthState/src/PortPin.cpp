#include "PortPin.h"

// Constructor
PortPin::PortPin() : Id(0), Type(PinType::Real), Mode(PinMode::Read), ValueType(ObjectValueType::Integer) {}

PortPin::PortPin(int Id, PinType PinType, PinMode PinMode, ObjectValueType ValueType):
	Id(Id), Value(""), Type(PinType), Mode(PinMode), ValueType(ValueType) {}

PortPin::PortPin(int Id, String &InitialValue, PinType PinType,PinMode &PinMode, ObjectValueType &ValueType, int ParentId):
	Id(Id), Value(InitialValue), Type(PinType), Mode(PinMode), ValueType(ValueType), ParentComponentId(ParentId) {}

// Getters and setters
int PortPin::getId() const
{ return Id; }

void PortPin::setId(int newId)
{ Id = newId; }

PinType PortPin::getType() const
{
	return Type;
}

void PortPin::setType(PinType &newType)
{
	Type = newType;
}

PinMode PortPin::getMode() const
{ return Mode; }

void PortPin::setMode(PinMode &newMode)
{ Mode = newMode; }

const String &PortPin::getValue() const
{ return Value; }

void PortPin::setValue(const String &newValue)
{ Value = newValue; }

ObjectValueType PortPin::getValueType() const
{ return ValueType; }

void PortPin::setValueType(ObjectValueType &newValueType)
{ ValueType = newValueType; }

int PortPin::getParentComponentId() const
{ return ParentComponentId; }

void PortPin::setParentComponentId(int parentComponentId)
{ ParentComponentId = parentComponentId; }

int PortPin::getOtherComponentId() const
{
	return OtherComponentId;
}

void PortPin::setOtherComponentId(int newId)
{
	OtherComponentId = newId;
}

int PortPin::getOtherComponentSequence() const
{
	return OtherComponentSequence;
}

void PortPin::setOtherComponentSequence(int newSequence)
{
	OtherComponentSequence = newSequence;
}
