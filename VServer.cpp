#pragma comment(lib, "ws2_32.lib") // линковка с  библиотекой ядра ОС
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>   // заголовочный файл, содержащий актуальные реализации функций для работы с сокетами.
#include <WS2tcpip.h>   // заголовочный файл, который содержит различные программные интерфейсы, связанные с работой протокола TCP/IP
#include <iostream>
#include <vector>
#include <thread>
#include "VServerHeart/VClientSocket.h"

int main(int argc, char* argv[])
{
    
    // soecket data and running
    WSADATA wsaData;                                    // ocket data struct
    WORD DlLLVerstion = MAKEWORD(2,1);
    if (WSAStartup(DlLLVerstion,&wsaData)!= 0)          // run
    {
        std::cout << "Error lib loading: " << WSAGetLastError() <<std::endl;
        exit(1);
    }

    
    // notwork information
    SOCKADDR_IN addresInfo;                                                       // SOCKADDR_IN used for add network data
    int sizeofaddr = sizeof(addresInfo);
    addresInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    addresInfo.sin_port = htons(1111);
    addresInfo.sin_family = AF_INET;
    
    // socket initialization
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    if (sListen == INVALID_SOCKET)
    {
        std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl;
        closesocket(sListen);
        WSACleanup();
        return 1;
    }
    
    // binding socket to addres and port (to transport level)
    bind(sListen, (SOCKADDR*)&addresInfo, sizeofaddr);
    listen(sListen,SOMAXCONN);
    std::cout << "Server pending new clients" << std::endl;

    SOCKADDR_IN newConnectionInfo;
    ZeroMemory(&newConnectionInfo, sizeof newConnectionInfo);
    std::vector<VClientSocket*> Clients;

    SOCKET NewConnection;
    NewConnection = accept(sListen, (SOCKADDR*)&newConnectionInfo, &sizeofaddr);
    if (NewConnection == 0)
    {
        std::cout << "Error, socket not created" << std::endl;
        return 1;
    }

    std::cout << "Connection success" << std::endl;
    char message[256] = "Hello new client";
    send(NewConnection, message,sizeof message, NULL);
    recv(NewConnection, message,sizeof(message),NULL);
    send(NewConnection, message,sizeof message, NULL);

    return 0;
}
