#pragma once
#include "Persistence.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"Ws2_32.lib")
#define WINSOCK_DEPRECATED_NO_WARNINGS

class ServerPersistence : Persistence
{
public:
	ServerPersistence(std::string IP, std::string port);
	bool Init() override;
	void Release() override;
protected:
	void Flush() override;
	SOCKET _socket;
	WSADATA* _data;
	std::string _IP, _port;
};