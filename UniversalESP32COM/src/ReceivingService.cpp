#include "ReceivingService.h"

ReceivingService::ReceivingService(UdpCommunication &UdpComm, EepromString &Eeprom, Board &newBoard) : udpComm(UdpComm), eeprom(Eeprom), board(newBoard)
{
	wakedUp = true;
}

void ReceivingService::runService()
{
	String data = udpComm.ReceiveMsg();

	if (data != "")
	{
		ReceivedDataPacket receivedDataPacket = JsonConverter::jsonToReceivedDataPacket(data);
		processCommands(receivedDataPacket);
		updateBoardPinsState();
	}

	if (wakedUp)
	{
		updateBoardPinsState();
		wakedUp = false;
	}
}

void ReceivingService::processCommands(ReceivedDataPacket &dataPacket)
{
	Serial.print("[RECEIVING] Incomming: ");
	Serial.print(dataPacket.getCommandsCount());
	Serial.println(" commands;");

	for (int i = 0; i < dataPacket.getCommandsCount(); i++)
	{
		ReceivedCommand command = dataPacket.getCommandByIndex(i);
		if (command.getAction() == CommandAction::SetId)
		{
			String commandValue = command.getValue();
			board.setId(commandValue);
			board.setConnectionState(true);
			if (eeprom.isInitialized())
			{
				eeprom.write(commandValue);
			}
		}
		else if (command.getAction() == CommandAction::SetValue)
		{
			int componentId = command.getComponentId();
			int pinId = command.getPinId();

			if (componentId != -1 && pinId != -1)
			{
				Component component = board.getComponentAtIndex(componentId);
				PortPin portPin = component.getConnectedPinAtIndex(pinId);
				portPin.setValue(command.getValue());
			}
		}
	}
}

void ReceivingService::updateBoardPinsState()
{
	for (int comp = 0; comp < board.getComponentCount(); comp++)
	{
		Component component = board.getComponentAtIndex(comp);
		for (int pin = 0; pin < component.getConnectedPinCount(); pin++)
		{
			PortPin portPin = component.getConnectedPinAtIndex(pin);
			if (portPin.getMode() == PinMode::Write)
			{
				ObjectValueType pinValueType = portPin.getValueType();
				if (pinValueType == ObjectValueType::Integer)
				{
					digitalWrite(portPin.getId(), portPin.getValue().toInt());
				}
				if (pinValueType == ObjectValueType::Float)
				{
					digitalWrite(portPin.getId(), portPin.getValue().toFloat());
				}
				else if (pinValueType == ObjectValueType::Boolean)
				{
					digitalWrite(portPin.getId(), portPin.getValue().toInt());
				}
			}
		}
	}
	Serial.println("<Arduino> Updated pins states");
}