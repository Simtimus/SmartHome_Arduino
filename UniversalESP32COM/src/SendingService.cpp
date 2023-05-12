#include "SendingService.h"

SendingService::SendingService(UdpCommunication &UdpComm, ComponentManager &CompManager, ArduinoDataPacket &DataPacket, Board &Board):
	udpComm(UdpComm), compManager(CompManager), dataPacket(DataPacket), board(Board), wakedUp(true) {}

void SendingService::runService()
{
	// Checking for an valid BoardId
	if (board.getId() == Board::DefaultGuid)
	{
		transmitBoardInfo();
		Serial.println("[SENDING] Transmited BoardInfo.");
	}
	else
	{
		if (wakedUp)
		{
			dataPacket.setBoardId(board.getId());
			board.setComponents(compManager.getComponents());
			board.setComponentsCount(compManager.getComponentsCount());
			Serial.println("<Arduino> Added Components to Board");
			updateChangedPinValues();
			transmitFullDevice();
			wakedUp = false;
		}
		else
		{
			bool changedPortPins[MAX_ITEMS][MAX_ITEMS];
			int changedPortPinsCount[MAX_ITEMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			updateChangedPinValues(changedPortPins, changedPortPinsCount);
			selectTransmissionMode(changedPortPins, changedPortPinsCount);
		}
	}
}

void SendingService::transmitBoardInfo()
{
	String serializedBoard = JsonConverter::boardToJson(board);
	dataPacket.setData(serializedBoard);
	dataPacket.setContentType(DataContentType::BoardInfo);
	String serializedClient = JsonConverter::clientDataToJson(dataPacket);
	udpComm.SendMsg(serializedClient);
	dataPacket.setToDefault();
	Serial.println("[SENDING] Transmited BoardInfo.");
	lastTransmission = millis();
}

void SendingService::transmitFullDevice()
{
	delay(500);
	String serializedBoard = JsonConverter::boardToJson(board);
	dataPacket.setData(serializedBoard, DataContentType::EntireBoard, board.getId());
	String serializedClient = JsonConverter::clientDataToJson(dataPacket);
	udpComm.SendMsg(serializedClient);
	dataPacket.setToDefault();
	Serial.println("[SENDING] Transmited FullDevice.");
	lastTransmission = millis();
}

void SendingService::transmitSingleComponent(int &componentIndex, bool (&changedPortPins)[MAX_ITEMS])
{
	Component &existingComponent = board.getComponentAtIndex(componentIndex);
	Component newComponent = Component(componentIndex, existingComponent.getComponentType(), existingComponent.getDescription());

	for (int i = 0; i < existingComponent.getConnectedPinCount(); i++)
	{
		if (changedPortPins[i])
		{
			newComponent.addConnectedPin(existingComponent.getConnectedPinAtIndex(i));
		}
	}

	String serializedPortPin = JsonConverter::componentToJson(newComponent);
	dataPacket.setData(serializedPortPin, board.getId(), componentIndex);
	String serializedClient = JsonConverter::clientDataToJson(dataPacket);
	udpComm.SendMsg(serializedClient);
	dataPacket.setToDefault();
	Serial.println("[SENDING] Transmited SingleComponent.");
	lastTransmission = millis();
}

void SendingService::transmitSinglePortPin(int &componentIndex, bool (&changedPortPins)[MAX_ITEMS])
{
	int portPinIndex = 0;
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (changedPortPins[i])
		{
			portPinIndex = i;
			break;
		}
	}

	Component &component = board.getComponentAtIndex(componentIndex);
	PortPin &portPin = component.getConnectedPinAtIndex(portPinIndex);

	Serial.print("<DEBUG> Component: "); Serial.print(componentIndex);
	Serial.print(" PinId: "); Serial.print(portPin.getId());
	Serial.print(" Value: "); Serial.println(portPin.getValue());

	String serializedPortPin = JsonConverter::portPinToJson(portPin);
	dataPacket.setData(serializedPortPin, board.getId(), componentIndex, portPin.getId());
	String serializedClient = JsonConverter::clientDataToJson(dataPacket);
	udpComm.SendMsg(serializedClient);
	dataPacket.setToDefault();
	Serial.println("[SENDING] Transmited SinglePortPin.");
	lastTransmission = millis();
}

void SendingService::updateChangedPinValues()
{
	int compCount = board.getComponentCount();
	for (int comp = 0; comp < compCount; comp++)
	{
		Component &component = board.getComponentAtIndex(comp);
		int pinCount = component.getConnectedPinCount();
		for (int pin = 0; pin < pinCount; pin++)
		{
			String readedValue;
			PortPin &portPin = component.getConnectedPinAtIndex(pin);
			if (portPin.getMode() == PinMode::Read)
			{
				if (portPin.getValueType() == ObjectValueType::Boolean)
					readedValue = String(digitalRead(portPin.getId()));
				else
					readedValue = String(digitalRead(portPin.getId()));

				if (portPin.getValue() != readedValue)
				{
					portPin.setValue(readedValue);
				}
			}
		}
	}
	Serial.println("<Arduino> Initial updated READING Pins");
}

void SendingService::updateChangedPinValues(bool (&changedPortPins)[MAX_ITEMS][MAX_ITEMS], int (&changedPortPinsCount)[MAX_ITEMS])
{
	bool componentChanged;
	int changedPinsCount;
	int compCount = board.getComponentCount();
	for (int comp = 0; comp < compCount; comp++)
	{
		changedPinsCount = 0;
		componentChanged = false;
		Component &component = board.getComponentAtIndex(comp);
		int pinCount = component.getConnectedPinCount();
		for (int pin = 0; pin < pinCount; pin++)
		{
			String readedValue;
			changedPortPins[comp][pin] = false;

				PortPin &portPin = component.getConnectedPinAtIndex(pin);
			if (portPin.getMode() == PinMode::Read)
			{
				if (portPin.getValueType() == ObjectValueType::Boolean)
					readedValue = String(digitalRead(portPin.getId()));
				else
					readedValue = String(digitalRead(portPin.getId()));

				if (portPin.getValue() != readedValue)
				{
					Serial.print("<Arduino> Changed [Component/PortPin]:[");
					Serial.print(comp); Serial.print("/");
					Serial.print(pin); Serial.print("] from `");
					Serial.print(portPin.getValue()); Serial.print("' to `");
					Serial.print(readedValue); Serial.println("'");

					portPin.setValue(readedValue);
					changedPinsCount++;
					componentChanged = true;
					changedPortPins[comp][pin] = true;
				}
			}
		}
		changedPortPinsCount[comp] = changedPinsCount;
	}
	if (componentChanged)
	{
		Serial.println("<Arduino> Updated READING Pins");
	}
}

void SendingService::selectTransmissionMode(bool (&changedPortPins)[MAX_ITEMS][MAX_ITEMS], int (&changedPortPinsCount)[MAX_ITEMS])
{
	int changedComponentCount = 0;
	int lastComponentIndex = 0;

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (changedPortPinsCount[i] > 0)
		{
			changedComponentCount++;
			lastComponentIndex = i;
		}
	}

	if (changedComponentCount == 1)
	{
		Serial.println("<Arduino> PinPort value changed");
		if (changedPortPinsCount[lastComponentIndex] == 1)
		{
			transmitSinglePortPin(lastComponentIndex, changedPortPins[lastComponentIndex]);
		}
		else
		{
			transmitSingleComponent(lastComponentIndex, changedPortPins[lastComponentIndex]);
		}
	}
	else if (changedComponentCount > 1)
	{
		Serial.println("<Arduino> PinPort value changed");
		transmitFullDevice();
	}
	else
	{
		if (!board.getConnectionState() and !wakedUp)
		{
			if (millis() - lastTransmission > 5000)
			{
				Serial.println("[SENDING] Waiting for server response");
				transmitFullDevice();
			}
		}
		else
		{
			if (millis() - lastTransmission > 40000)
			{
				Serial.print("[SENDING] Time from last transmission: ");
				Serial.println(millis() - lastTransmission);
				transmitFullDevice();
			}
		}
	}
}