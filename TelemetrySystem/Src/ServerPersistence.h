#pragma once
#include "Persistence.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"Ws2_32.lib")
#define WINSOCK_DEPRECATED_NO_WARNINGS

class ServerPersistence : public Persistence
{
public:
	ServerPersistence();
	bool Init(std::string IP, std::string port);
	void Release() override;
protected:
	bool Flush() override;
	SOCKET _socket;
	WSADATA* _data;
	std::string _IP, _port;
};