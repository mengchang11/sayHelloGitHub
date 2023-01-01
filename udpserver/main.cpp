#include "common.h"

int main()
{
    std::cout << "Welcome to Here." << std::endl;

    UdpServer udpServer;
    udpServer.StartUdpServer();

    return 0;
}