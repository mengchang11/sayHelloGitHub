#include <iostream>

#include "common.h"
#include "udpClient.h"

int main()
{
    std::cout << "-----Hello udp client-----" << std::endl;

    UdpClient udpClient;
    udpClient.StartUdpClient();

    std::cout << "-----Bye udp client-----" << std::endl;
}