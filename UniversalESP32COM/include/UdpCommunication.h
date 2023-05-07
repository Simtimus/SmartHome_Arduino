#pragma once
#ifndef UDPCOMMUNICATION_H
#define UDPCOMMUNICATION_H

// Arduino Libraries
#include <Arduino.h>
// WiFi Librarries
#include <WiFiUdp.h>
// Project Libraries
// ...

class UdpCommunication
{
	public:
		// Constructor
		UdpCommunication(WiFiUDP &udp, const char *host, uint16_t port);

		int SendMsg(String msg);
		String ReceiveMsg();

	private:
		WiFiUDP &_udp;
		const char *_host;
		uint16_t _port;
};

#endif // UDPCOMMUNICATION_H
