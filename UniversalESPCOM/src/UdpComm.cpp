// Arduino Libraries
#include <Arduino.h>
// WiFi Librarries
#include <WiFiUdp.h>
// Project Libraries
#include <UdpComm.h>

int UdpCommunication::SendMsg(String msg)
{
	_udp.beginPacket(_host, _port);
	int packetSize = _udp.print(msg);
	_udp.endPacket();

	return packetSize;
}

String UdpCommunication::ReciveMsg()
{
	int packetSize = _udp.parsePacket();
	String msg = "";

	if (packetSize)
	{
		char incomingPacket[256];
		int len = _udp.read(incomingPacket, 255);
		if (len > 0)
		{
			incomingPacket[len] = 0;
		}

		for (size_t i = 0; i < len; i++)
		{
			msg += incomingPacket[i];
		}
	}

	return msg;
}