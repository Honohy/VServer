#pragma once
#include <WinSock2.h>

class VClientSocket
{
public:
    explicit VClientSocket(SOCKET* InClientSocket, size_t InClientId);
    SOCKET* MyCosketRef;
    void BufferHandling();
    
};
