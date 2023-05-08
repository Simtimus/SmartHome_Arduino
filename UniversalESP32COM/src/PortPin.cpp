#include "PortPin.h"

// Constructor
PortPin::PortPin() : Id(0), Mode(PinMode::Read), ValueType(ObjectValueType::Integer) {}

PortPin::PortPin(int Id, PinMode PinMode, ObjectValueType ValueType):
	Id(Id), Value(""), Mode(PinMode), ValueType(ValueType) {}

PortPin::PortPin(int Id, String InitialValue, PinMode PinMode, ObjectValueType ValueType):
	Id(Id), Value(InitialValue), Mode(PinMode), ValueType(ValueType) {}

// Getters and setters
int PortPin::getId() const
{ return Id; }

void PortPin::setId(int newId)
{ Id = newId; }

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
