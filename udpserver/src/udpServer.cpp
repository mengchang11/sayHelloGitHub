#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "udpServer.h"

UdpServer::UdpServer()
{
    std::cout << "-----Create udp server-----" << std::endl;
    m_udpServer = -1;

    memset(m_recvDataBuffer, 0, sizeof(m_recvDataBuffer));

    // Init server info
    memset(&m_serverInfo, 0, sizeof(m_serverInfo));
    m_serverInfo.sin_family = AF_INET;
    m_serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    m_serverInfo.sin_port = htons(7777);

    memset(&m_clientInfo, 0, sizeof(m_clientInfo));
    m_lenClientInfo = 0;
}

UdpServer::~UdpServer()
{
    std::cout << "-----Destory resource start-----" << std::endl;

    if (m_udpServer != -1) {
        close(m_udpServer);
        m_udpServer = -1;
    }
    
    std::cout << "-----Destory resource end  -----" << std::endl;
}

int UdpServer::SendDatatoClient()
{
    memset(m_recvDataBuffer, 0, sizeof(m_recvDataBuffer));

    strcpy(m_recvDataBuffer, "Hello client.");
    int ret = sendto(m_udpServer, m_recvDataBuffer, strlen(m_recvDataBuffer), 0,
        (sockaddr*)&m_clientInfo, m_lenClientInfo);
    if (ret == -1) {
        std::cout << "Send data to client error." << errno << std::endl;
        perror("sendto");
        return -1;
    }

    return 0;
}

int UdpServer::HandleRecv()
{
    while(1) {

        // Clear client info and recv data buffer
        memset(&m_clientInfo, 0, sizeof(m_clientInfo));
        memset(m_recvDataBuffer, 0, sizeof(m_recvDataBuffer));

        // client info need init sizeof(m_clientInfo) !!!
        m_lenClientInfo = sizeof(m_clientInfo);

        // Recv data from server socket
        int ret = recvfrom(m_udpServer, m_recvDataBuffer, sizeof(m_recvDataBuffer), 0,
            (sockaddr*)&m_clientInfo, &m_lenClientInfo);
        if (ret == -1) {
            std::cout << "Recv data from socket error." << std::endl;
            continue;
        }

        // Print data
        std::cout << inet_ntoa(m_clientInfo.sin_addr) << " " << ntohs(m_clientInfo.sin_port) << " says: " <<
            m_recvDataBuffer << std::endl;

        // Waitting 2 seconds send data
        sleep(2);
    
        // Say "Hello client" to client
        SendDatatoClient();
    }
}

int UdpServer::StartUdpServer()
{
    std::cout << "-----Hello udp server-----" << std::endl;
    m_udpServer = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_udpServer == -1) {
        std::cout << "Create socket error." << std::endl;
        return -1;
    }

    // Bind server info
    int ret = bind(m_udpServer, (const sockaddr*)&m_serverInfo, sizeof(m_serverInfo));
    if (ret != 0) {
        std::cout << "Bind serverinfo error." << std::endl;
        return -1;
    }

    // Recv data
    HandleRecv();

    std::cout << "----- Bye udp server -----" << std::endl;

    return 0;
}