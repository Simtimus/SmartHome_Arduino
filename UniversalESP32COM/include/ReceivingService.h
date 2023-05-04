#ifndef RECEIVING_SERVICE_H
#define RECEIVING_SERVICE_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "Board.h"

enum class DataContentType
{
	// IDK ...
	// First of all I have to think better how
	// I would use this class, and if I would
	// use it for both ATmega and ESP or only
	// for one, so each would have its optimized
	// version

};

class ReceivingService
{
public:
	ReceivingService();
	ReceivingService(String &boardId);
	ReceivingService(String &boardId, int &componentId);
	ReceivingService(String &boardId, int &componentId, int &pinId);

	void setData(const String &newData);

	void setData(const String &newData, const DataContentType &contentType, const String &newBoardId);

	void setData(const String &newData, const String &newBoardId, const int &newComponentId);

	void setData(const String &newData, const String &newBoardId, const int &newComponentId, const int &newPinId);

	void setContentType(const DataContentType &newContentType);

	void setBoardId(const String &newBoardId);

	void setComponentId(const int &newComponentId);

	void setPinId(const int &newPinId);

	void setToDefault();

private:
	DataContentType ContentType;
	int ComponentId = -1;
	int PinId = -1;
};

#endif // RECEIVING_SERVICE_H
