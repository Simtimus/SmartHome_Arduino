#include "JsonConverter.h"

// -------------------------------------------------------
// SERIALIZERS

String JsonConverter::portPinToJson(const PortPin &portPin)
{
	size_t portPinDocSize = GetPortPinDocummentSize(portPin);
	DynamicJsonDocument doc(portPinDocSize);

	doc["Id"] = portPin.getId();
	doc["Mode"] = static_cast<int>(portPin.getMode());
	doc["Value"] = portPin.getValue();
	doc["ValueType"] = static_cast<int>(portPin.getValueType());
	doc["ParentComponentId"] = portPin.getParentComponentId();

	String json;
	serializeJson(doc, json);
	return json;
}

String JsonConverter::componentToJson(const Component &component)
{
	size_t componentDocSize = GetComponentDocummentSize(component);
	DynamicJsonDocument doc(componentDocSize);

	doc["Id"] = component.getId();
	doc["ComponentId"] = static_cast<int>(component.getComponentId());
	doc["Description"] = component.getDescription();

	JsonArray connectedPinsArray = doc.createNestedArray("ConnectedPins");
	for (int j = 0; j < component.getConnectedPinCount(); j++)
	{
		JsonObject connectedPinObj = connectedPinsArray.createNestedObject();
		const PortPin &pin = component.getConnectedPinAtIndex(j);

		connectedPinObj["Id"] = pin.getId();
		connectedPinObj["ContentType"] = static_cast<int>(pin.getMode());
		connectedPinObj["Value"] = pin.getValue();
		connectedPinObj["ValueType"] = static_cast<int>(pin.getValueType());
		connectedPinObj["ParentComponentId"] = pin.getParentComponentId();
	}

	String json;
	serializeJson(doc, json);
	return json;
}

String JsonConverter::boardToJson(const Board &board)
{
	size_t boardDocSize = GetBoardDocummentSize(board);
	DynamicJsonDocument doc(boardDocSize);

	doc["Id"] = board.getId();
	doc["Name"] = board.getName();
	doc["Model"] = board.getModel();
	doc["Description"] = board.getDescription();

	JsonArray componentsArray = doc.createNestedArray("Components");
	for (int i = 0; i < board.getComponentCount(); i++)
	{
		JsonObject componentObj = componentsArray.createNestedObject();
		const Component &component = board.getComponentAtIndex(i);

		componentObj["Id"] = component.getId();
		componentObj["ComponentId"] = static_cast<int>(component.getComponentId());
		componentObj["Description"] = component.getDescription();

		JsonArray connectedPinsArray = componentObj.createNestedArray("ConnectedPins");
		for (int j = 0; j < component.getConnectedPinCount(); j++)
		{
			JsonObject connectedPinObj = connectedPinsArray.createNestedObject();
			const PortPin &pin = component.getConnectedPinAtIndex(j);

			connectedPinObj["Id"] = pin.getId();
			connectedPinObj["Mode"] = static_cast<int>(pin.getMode());
			connectedPinObj["Value"] = pin.getValue();
			connectedPinObj["ValueType"] = static_cast<int>(pin.getValueType());
			connectedPinObj["ParentComponentId"] = pin.getParentComponentId();
		}
	}

	String json;
	serializeJson(doc, json);
	return json;
}

String JsonConverter::clientDataToJson(const ArduinoDataPacket &dataPacket)
{
	size_t clientDataDocSize = GetClientDataDocummentSize(dataPacket);
	DynamicJsonDocument doc(clientDataDocSize);

	doc["Data"] = dataPacket.getData();
	doc["ContentType"] = static_cast<int>(dataPacket.getContentType());
	doc["BoardId"] = dataPacket.getBoardId();
	doc["ComponentId"] = dataPacket.getComponentId();
	doc["PinId"] = dataPacket.getPinId();

	String json;
	serializeJson(doc, json);
	return json;
}

// -------------------------------------------------------
// DESERIALIZERS

Board JsonConverter::jsonToBoard(const String &json)
{

	DynamicJsonDocument doc(json.length() + 128);
	deserializeJson(doc, json);

	Board board(
		doc["Id"].as<String>(),
		doc["Name"].as<String>(),
		doc["Model"].as<String>(),
		doc["Description"].as<String>());

	JsonArray componentsArray = doc["Components"];
	for (JsonObject componentObj : componentsArray)
	{
		Component component(
			componentObj["Id"].as<int>(),
			static_cast<ComponentsId>(componentObj["ComponentId"].as<int>()),
			componentObj["Description"].as<String>());

		JsonArray connectedPinsArray = componentObj["ConnectedPins"];
		for (JsonObject connectedPinObj : connectedPinsArray)
		{
			PortPin pin(
				connectedPinObj["Id"].as<int>(),
				static_cast<PinMode>(connectedPinObj["Mode"].as<int>()),
				static_cast<ObjectValueType>(connectedPinObj["ValueType"].as<int>()));
			pin.setValue(connectedPinObj["Value"].as<String>());
			pin.setParentComponentId(connectedPinObj["ParentComponentId"].as<int>());

			component.addConnectedPin(pin);
		}

		board.addComponent(component);
	}

	return board;
}

Component JsonConverter::jsonToComponent(const String &json)
{
	DynamicJsonDocument doc(json.length() + 128);
	deserializeJson(doc, json);

	Component component(
		doc["Id"].as<int>(),
		static_cast<ComponentsId>(doc["ComponentId"].as<int>()),
		doc["Description"].as<String>());

	JsonArray connectedPinsArray = doc["ConnectedPins"];
	for (JsonObject connectedPinObj : connectedPinsArray)
	{
		PortPin pin(
			connectedPinObj["Id"].as<int>(),
			static_cast<PinMode>(connectedPinObj["Mode"].as<int>()),
			static_cast<ObjectValueType>(connectedPinObj["ValueType"].as<int>()));
		pin.setValue(connectedPinObj["Value"].as<String>());
		pin.setParentComponentId(connectedPinObj["ParentComponentId"].as<int>());

		component.addConnectedPin(pin);
	}

	return component;
}

PortPin JsonConverter::jsonToPortPin(const String &json)
{
	DynamicJsonDocument doc(json.length() + 128);
	deserializeJson(doc, json);

	PortPin pin(
		doc["Id"].as<int>(),
		static_cast<PinMode>(doc["Mode"].as<int>()),
		static_cast<ObjectValueType>(doc["ValueType"].as<int>()));
	pin.setValue(doc["Value"].as<String>());
	pin.setParentComponentId(doc["ParentComponentId"].as<int>());

	return pin;
}

ArduinoDataPacket JsonConverter::jsonToClientData(const String &json)
{
	DynamicJsonDocument doc(json.length() + 128);
	deserializeJson(doc, json);

	ArduinoDataPacket clientData;
	clientData.setData(doc["Data"].as<String>());
	clientData.setContentType(static_cast<DataContentType>(doc["ContentType"].as<int>()));
	clientData.setBoardId(doc["BoardId"].as<String>());
	clientData.setComponentId(doc["ComponentId"].as<int>());
	clientData.setPinId(doc["PinId"].as<int>());

	return clientData;
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

size_t JsonConverter::GetClientDataDocummentSize(const ArduinoDataPacket &dataPacket)
{
	size_t baseSize = 150;
	baseSize += dataPacket.getData().length();
	baseSize += dataPacket.getBoardId().length();

	return baseSize;
}