#ifndef PORT_PIN_H
#define PORT_PIN_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
// ...

enum class PinMode
{
	Read,
	Write,
	Virtual, // Conventional -> Id >= 100
};

enum class ObjectValueType
{
	String,
	Integer,
	Float,
	Boolean,
};

class PortPin
{
public:
	// Constructor
	PortPin();

	PortPin(int Id, PinMode PinMode, ObjectValueType ValueType);

	PortPin(int Id, String InitialValue, PinMode PinMode, ObjectValueType ValueType);

	// Getters and setters
	int getId() const;
	void setId(int newId);

	PinMode getMode() const;
	void setMode(PinMode newMode);

	String getValue() const;
	void setValue(const String &newValue);

	ObjectValueType getValueType() const;
	void setValueType(ObjectValueType newValueType);

	int getParentComponentId() const;
	void setParentComponentId(int parentComponentId);

private:
	int Id;
	PinMode Mode;
	String Value;
	ObjectValueType ValueType;
	int ParentComponentId;
};

#endif // PORT_PIN_H
