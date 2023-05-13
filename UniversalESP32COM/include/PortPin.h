#ifndef PORT_PIN_H
#define PORT_PIN_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
// ...

enum class PinType
{
	Real,	 // Conventional -> Id >= 100
	Virtual, // Conventional -> Id >= 100
};

enum class PinMode
{
	Read,
	Write,
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

	PortPin(int Id, PinType PinType, PinMode PinMode, ObjectValueType ValueType);

	PortPin(int &Id, String &InitialValue, PinType PinType, PinMode &PinMode, ObjectValueType &ValueType, int ParentId);

	// Getters and setters
	int getId() const;
	void setId(int &newId);

	PinType getType() const;
	void setType(PinType &newType);

	PinMode getMode() const;
	void setMode(PinMode &newMode);

	const String &getValue() const;
	void setValue(const String &newValue);

	ObjectValueType getValueType() const;
	void setValueType(ObjectValueType &newValueType);

	int getParentComponentId() const;
	void setParentComponentId(int parentComponentId);

	int getOtherComponentId() const;
	void setOtherComponentId(int newId);

	int getOtherComponentSequence() const;
	void setOtherComponentSequence(int newSequence);

private:
	int Id;
	PinType Type;
	PinMode Mode;
	String Value;
	ObjectValueType ValueType;
	int ParentComponentId;

	int OtherComponentId;
	int OtherComponentSequence;
};

#endif // PORT_PIN_H
