#ifndef JSON_CONVERTER_H
#define JSON_CONVERTER_H

#include <Arduino.h>
#include "Board.h"
#include "Component.h"
#include "PortPin.h"

class JsonConverter
{
public:
	static String portPinToJson(const PortPin &portPin);
	static String componentToJson(const Component &component);
	static String boardToJson(const Board &board);

	static size_t GetPortPinDocummentSize(const PortPin &portPin);
	static size_t GetComponentDocummentSize(const Component &component);
	static size_t GetBoardDocummentSize(const Board &board);

	static Board jsonToBoard(const String &json);
};

#endif // JSON_CONVERTER_H
