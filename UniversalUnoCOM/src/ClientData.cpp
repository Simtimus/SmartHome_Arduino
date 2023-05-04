#include "ClientData.h"

ClientData::ClientData() {}

ClientData::ClientData(String &boardId) : BoardId(boardId) {}

ClientData::ClientData(String &boardId, int &componentId) : BoardId(boardId), ComponentId(componentId) {}

ClientData::ClientData(String &boardId, int &componentId, int &pinId) : BoardId(boardId), ComponentId(componentId), PinId(pinId) {}

void ClientData::setData(const String &newData)
{
	Data = newData;
	ContentType = DataContentType::StringMessage;
}

void ClientData::setData(const String &newData, const DataContentType &contentType, const String &newBoardId)
{
	Data = newData;
	ContentType = contentType;
	BoardId = newBoardId;
}

void ClientData::setData(const String &newData, const String &newBoardId, const int &newComponentId)
{
	Data = newData;
	BoardId = newBoardId;
	ComponentId = newComponentId;
	ContentType = DataContentType::SingleComponent;
}

void ClientData::setData(const String &newData, const String &newBoardId, const int &newComponentId, const int &newPinId)
{
	Data = newData;
	BoardId = newBoardId;
	ComponentId = newComponentId;
	PinId = newPinId;
	ContentType = DataContentType::SinglePortPin;
}

void ClientData::setContentType(const DataContentType &newContentType)
{
	ContentType = newContentType;
}

void ClientData::setBoardId(const String &newBoardId)
{
	BoardId = newBoardId;
}

void ClientData::setComponentId(const int &newComponentId)
{
	ComponentId = newComponentId;
}

void ClientData::setPinId(const int &newPinId)
{
	PinId = newPinId;
}

void ClientData::setToDefault()
{
	Data = "";
	ContentType = DataContentType::StringMessage;
	int ComponentId = -1;
	int PinId = -1;
}
