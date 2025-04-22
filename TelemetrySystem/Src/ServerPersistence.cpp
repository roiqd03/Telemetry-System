#include "ServerPersistence.h"

ServerPersistence::ServerPersistence() : Persistence()
{
    _socket = INVALID_SOCKET;
    _data = nullptr;
}

bool ServerPersistence::Init(std::string IP, std::string port)
{
    _IP = IP;
    _port = port;

    int iResult = WSAStartup(MAKEWORD(2, 2), _data); //El parámetro MAKEWORD(2,2) realiza una solicitud para la versión 2.2 de Winsock en el sistema
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return false;
    }

    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(_IP.c_str(), _port.c_str(), &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        return false;
    }

    ptr = result;
    // Creamos el socket con el que conectarse 
    _socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (_socket == INVALID_SOCKET) {
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    iResult = connect(_socket, ptr->ai_addr, ptr->ai_addrlen);
    if (iResult == -1) {
        closesocket(_socket);
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    freeaddrinfo(result);
    return true;
}

void ServerPersistence::Release()
{
    closesocket(_socket);
    WSACleanup();
}

bool ServerPersistence::Flush()
{
    if (_socket == INVALID_SOCKET) return false;
    std::string s = SuddenSerialization();
    int length = s.length();
    int iResult = send(_socket, s.c_str(), length, 0);
    if (iResult == -1) {
        /*printf("Something has gone wrong");
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        WSACleanup();*/
        return false;
    }
    return true;
}
