#ifndef JSON_CONVERTER_H
#define JSON_CONVERTER_H

// Arduino Libraries
#include <Arduino.h>
#include <ArduinoJson.h>
// Project Libraries
#include "ReceivedDataPacket.h"
#include "ArduinoDataPacket.h"
#include "Board.h"
#include "Component.h"
#include "PortPin.h"

class JsonConverter
{
public:
	static String portPinToJson(const PortPin &portPin);
	static String componentToJson(const Component &component);
	static String boardToJson(const Board &board);
	static String clientDataToJson(const ArduinoDataPacket &dataPacket);

	static Board jsonToBoard(const String &json);
	static Component jsonToComponent(const String &json);
	static PortPin jsonToPortPin(const String &json);
	static ArduinoDataPacket jsonToClientData(const String &json);
	static ReceivedDataPacket jsonToReceivedDataPacket(const String &json);

	static size_t GetPortPinDocummentSize(const PortPin &portPin);
	static size_t GetComponentDocummentSize(const Component &component);
	static size_t GetBoardDocummentSize(const Board &board);
	static size_t GetClientDataDocummentSize(const ArduinoDataPacket &dataPacket);
};

#endif // JSON_CONVERTER_H
