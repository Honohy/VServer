#include "VClientSocket.h"

#include <iostream>

VClientSocket::VClientSocket(SOCKET* InClientSocket, size_t InClientId)
{
    MyCosketRef = InClientSocket;
    std::cout << "Client " << InClientId << " connected" << std::endl;
}

void VClientSocket::BufferHandling()
{
    
    std::cout << "Client" << " connected" << std::endl;
    std::string StartMessage = "Hello new client";
    char NewMessage[256];
    for (int i = 0; i < sizeof StartMessage; i++)
    {
        NewMessage[i] = StartMessage[i];
        std::cout << NewMessage[i] << std::endl;
    }
    
    //send(*MyCosketRef,NewMessage,256,NULL);

}
