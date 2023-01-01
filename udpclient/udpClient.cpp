#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#include "udpClient.h"

UdpClient::UdpClient()
{
    std::cout << "-----Create udp client-----" << std::endl;

    m_udpClient = -1;

    // Init recv info
    memset(&m_serverInfo, 0, sizeof(m_serverInfo));
    m_serverInfo.sin_family = AF_INET;
    m_serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    m_serverInfo.sin_port = htons(7777);

    m_loopNum = 10;
}

UdpClient::~UdpClient()
{
    std::cout << "-----Destory udp client start-----" << std::endl;

    if (m_udpClient != -1) {
        close(m_udpClient);
        m_udpClient = -1;
    }

    std::cout << "-----Destroy udp client end-----" << std::endl;
}

int UdpClient::RecvData()
{
    sockaddr_in clientInfo;
    socklen_t lenClientInfo = 0;
    int ret = recvfrom(m_udpClient, m_sendDataBuffer, sizeof(m_sendDataBuffer), 0,
        (sockaddr*)&clientInfo, &lenClientInfo);
    if (ret == -1) {
        std::cout << "Recv data from socket error." << std::endl;
        return -1;
    }
    std::cout << inet_ntoa(clientInfo.sin_addr) << " " << ntohs(clientInfo.sin_port) << " says: " <<
        m_sendDataBuffer << std::endl;
    
    // Sleep 2 seconds to send data
    sleep(2);

    return 0;
}

int UdpClient::SendDataToServer()
{
    while(1) {
        socklen_t serverInfoLen = sizeof(m_serverInfo);
        char *funRet = strcpy(m_sendDataBuffer, "Hello server.");
        int ret = sendto(m_udpClient, m_sendDataBuffer, strlen(m_sendDataBuffer), 0,
            (sockaddr*)&m_serverInfo, serverInfoLen);
        if (ret == -1) {
            std::cout << "Send data to server error." << std::endl;

            // Have error sleep 2 seconds and continue
            sleep(2);
            continue;;
        }

        // Recv data
        RecvData();
    }
    
    return 0;
}

int UdpClient::StartUdpClient()
{
    std::cout << "-----Strat udp client-----" << std::endl;

    m_udpClient = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_udpClient == -1) {
        std::cout << "Create socket error." << std::endl;
        return -1;
    }

    // Save recv msg server info
    SendDataToServer();

    std::cout << "-----End udp client-----" << std::endl;

    return 0;
}