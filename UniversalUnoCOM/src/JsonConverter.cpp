#include "JsonConverter.h"
#include <ArduinoJson.h>

// -------------------------------------------------------
// SERIALIZERS

String JsonConverter::portPinToJson(const PortPin &portPin)
{
	size_t portPinDocSize = GetPortPinDocummentSize(portPin);
	DynamicJsonDocument doc(portPinDocSize);

	doc["id"] = portPin.getId();
	doc["mode"] = static_cast<int>(portPin.getMode());
	doc["value"] = portPin.getValue();
	doc["valueType"] = static_cast<int>(portPin.getValueType());
	doc["parentComponentId"] = portPin.getParentComponentId();

	String json;
	serializeJson(doc, json);
	return json;
}

String JsonConverter::componentToJson(const Component &component)
{
	size_t componentDocSize = GetComponentDocummentSize(component);
	DynamicJsonDocument doc(componentDocSize);

	doc["id"] = component.getId();
	doc["componentId"] = static_cast<int>(component.getComponentId());
	doc["description"] = component.getDescription();

	JsonArray connectedPinsArray = doc.createNestedArray("connectedPins");
	for (int j = 0; j < component.getConnectedPinCount(); j++)
	{
		JsonObject connectedPinObj = connectedPinsArray.createNestedObject();
		const PortPin &pin = component.getConnectedPinAtIndex(j);

		connectedPinObj["id"] = pin.getId();
		connectedPinObj["mode"] = static_cast<int>(pin.getMode());
		connectedPinObj["value"] = pin.getValue();
		connectedPinObj["valueType"] = static_cast<int>(pin.getValueType());
		connectedPinObj["parentComponentId"] = pin.getParentComponentId();
	}

	String json;
	serializeJson(doc, json);
	return json;
}

String JsonConverter::boardToJson(const Board &board)
{
	size_t boardDocSize = GetBoardDocummentSize(board);
	DynamicJsonDocument doc(boardDocSize);

	doc["id"] = board.getId();
	doc["name"] = board.getName();
	doc["model"] = board.getModel();
	doc["description"] = board.getDescription();

	JsonArray componentsArray = doc.createNestedArray("components");
	for (int i = 0; i < board.getComponentCount(); i++)
	{
		JsonObject componentObj = componentsArray.createNestedObject();
		const Component &component = board.getComponentAtIndex(i);

		componentObj["id"] = component.getId();
		componentObj["componentId"] = static_cast<int>(component.getComponentId());
		componentObj["description"] = component.getDescription();

		JsonArray connectedPinsArray = componentObj.createNestedArray("connectedPins");
		for (int j = 0; j < component.getConnectedPinCount(); j++)
		{
			JsonObject connectedPinObj = connectedPinsArray.createNestedObject();
			const PortPin &pin = component.getConnectedPinAtIndex(j);

			connectedPinObj["id"] = pin.getId();
			connectedPinObj["mode"] = static_cast<int>(pin.getMode());
			connectedPinObj["value"] = pin.getValue();
			connectedPinObj["valueType"] = static_cast<int>(pin.getValueType());
			connectedPinObj["parentComponentId"] = pin.getParentComponentId();
		}
	}

	String json;
	serializeJson(doc, json);
	return json;
}

// -------------------------------------------------------
// DESERIALIZERS

Board JsonConverter::jsonToBoard(const String &json)
{

	DynamicJsonDocument doc(2048);
	deserializeJson(doc, json);

	Board board(
		doc["id"].as<String>(),
		doc["name"].as<String>(),
		doc["model"].as<String>(),
		doc["description"].as<String>());

	JsonArray componentsArray = doc["components"];
	for (JsonObject componentObj : componentsArray)
	{
		Component component(
			componentObj["id"].as<int>(),
			static_cast<ComponentsId>(componentObj["componentId"].as<int>()),
			componentObj["description"].as<String>());

		JsonArray connectedPinsArray = componentObj["connectedPins"];
		for (JsonObject connectedPinObj : connectedPinsArray)
		{
			PortPin pin(
				connectedPinObj["id"].as<int>(),
				static_cast<PinMode>(connectedPinObj["mode"].as<int>()),
				static_cast<ObjectValueType>(connectedPinObj["valueType"].as<int>()));
			pin.setValue(connectedPinObj["value"].as<String>());
			pin.setParentComponentId(connectedPinObj["parentComponentId"].as<int>());

			component.addConnectedPin(pin);
		}

		board.addComponent(component);
	}

	return board;
}

// -------------------------------------------------------
// Optimized Documment Size

size_t JsonConverter::GetPortPinDocummentSize(const PortPin &portPin)
{
	size_t baseSize = 70;
	size_t extraSize = portPin.getValue().length();
	return baseSize + extraSize;
}

size_t JsonConverter::GetComponentDocummentSize(const Component &component)
{
	size_t baseSize = 64;
	size_t portPinSize = 0;
	baseSize += component.getDescription().length();

	for (int i = 0; i < component.getConnectedPinCount(); i++)
	{
		const PortPin &pin = component.getConnectedPinAtIndex(i);
		portPinSize += GetPortPinDocummentSize(pin);
	}

	return baseSize + portPinSize;
}

size_t JsonConverter::GetBoardDocummentSize(const Board &board)
{
	size_t baseSize = 100;
	size_t componentSize = 0;
	baseSize += board.getName().length();
	baseSize += board.getModel().length();
	baseSize += board.getDescription().length();

	for (int i = 0; i < board.getComponentCount(); i++)
	{
		const Component &component = board.getComponentAtIndex(i);
		componentSize += GetComponentDocummentSize(component);
	}

	return baseSize + componentSize;
}