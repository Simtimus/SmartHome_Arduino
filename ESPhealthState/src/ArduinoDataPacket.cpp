#include "ArduinoDataPacket.h"

ArduinoDataPacket::ArduinoDataPacket() {}

ArduinoDataPacket::ArduinoDataPacket(String &boardId) : BoardId(boardId) {}

ArduinoDataPacket::ArduinoDataPacket(String &boardId, int &componentId) : BoardId(boardId), ComponentId(componentId) {}

ArduinoDataPacket::ArduinoDataPacket(String &boardId, int &componentId, int &pinId) : BoardId(boardId), ComponentId(componentId), PinId(pinId) {}

void ArduinoDataPacket::setData(const String &newData)
{
	Data = newData;
	ContentType = DataContentType::StringMessage;
}

void ArduinoDataPacket::setData(const String &newData, const DataContentType &contentType, const String &newBoardId)
{
	Data = newData;
	ContentType = contentType;
	BoardId = newBoardId;
}

void ArduinoDataPacket::setData(const String &newData, const String &newBoardId, const int &newComponentId)
{
	Data = newData;
	BoardId = newBoardId;
	ComponentId = newComponentId;
	ContentType = DataContentType::SingleComponent;
}

void ArduinoDataPacket::setData(const String &newData, const String &newBoardId, const int &newComponentId, const int &newPinId)
{
	Data = newData;
	BoardId = newBoardId;
	ComponentId = newComponentId;
	PinId = newPinId;
	ContentType = DataContentType::SinglePortPin;
}

void ArduinoDataPacket::setContentType(const DataContentType &newContentType)
{
	ContentType = newContentType;
}

void ArduinoDataPacket::setBoardId(const String &newBoardId)
{
	BoardId = newBoardId;
}

void ArduinoDataPacket::setComponentId(const int &newComponentId)
{
	ComponentId = newComponentId;
}

void ArduinoDataPacket::setPinId(const int &newPinId)
{
	PinId = newPinId;
}

void ArduinoDataPacket::setToDefault()
{
	Data = "";
	ContentType = DataContentType::StringMessage;
	int ComponentId = -1;
	int PinId = -1;
}

String ArduinoDataPacket::getData() const
{
	return Data;
}

DataContentType ArduinoDataPacket::getContentType() const
{
	return ContentType;
}

String ArduinoDataPacket::getBoardId() const
{
	return BoardId;
}

int ArduinoDataPacket::getComponentId() const
{
	return ComponentId;
}

int ArduinoDataPacket::getPinId() const
{
	return PinId;
}