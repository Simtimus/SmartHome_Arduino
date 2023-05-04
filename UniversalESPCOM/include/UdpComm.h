#pragma once
#ifndef UDPCOMM_H
#define UDPCOMM_H

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
		UdpCommunication(WiFiUDP &udp, char *host, uint16_t port):
			_udp(udp), _host(host), _port(port) {};

		int SendMsg(String msg);
		String ReciveMsg();

	private:
		WiFiUDP &_udp;
		char *_host;
		uint16_t _port;
};

#endif // UDPCOMM_H
