#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H

// Arduino Libraries
#include <Arduino.h>
// Prooject Libraries
#include "Board.h"

enum class DataContentType
{
	StringMessage,
	BoardInfo,
	EntireBoard,
	SingleComponent,
	SinglePortPin,
};

class ClientData
{
public:
	ClientData();
	ClientData(String &boardId);
	ClientData(String &boardId, int &componentId);
	ClientData(String &boardId, int &componentId, int &pinId);

	void setData(const String &newData);

	void setData(const String &newData, const DataContentType &contentType, const String &newBoardId);

	void setData(const String &newData, const String &newBoardId, const int &newComponentId);

	void setData(const String &newData, const String &newBoardId, const int &newComponentId, const int &newPinId);

	void setContentType(const DataContentType &newContentType);

	void setBoardId(const String &newBoardId);

	void setComponentId(const int &newComponentId);

	void setPinId(const int &newPinId);

	void setToDefault();

	String getData() const;
	DataContentType getContentType() const;
	String getBoardId() const;
	int getComponentId() const;
	int getPinId() const;
	
private:
	String Data;
	DataContentType ContentType;
	String BoardId;
	int ComponentId = -1;
	int PinId = -1;
};

#endif // CLIENT_DATA_H
