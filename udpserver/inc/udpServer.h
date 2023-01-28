#include <iostream>
#include <arpa/inet.h>

class UdpServer {
public:
    UdpServer();
    ~UdpServer();

    // Create and start a server
    int StartUdpServer();

protected:

    // Start handle recv data
    int HandleRecv();

    // Send server data to client
    int SendDatatoClient();
private:

    // Save udp socket
    int m_udpServer;

    // Save server info
    struct sockaddr_in m_serverInfo;

    // Save client info
    struct sockaddr_in m_clientInfo;
    socklen_t m_lenClientInfo;

    // Save recv date
    char m_recvDataBuffer[1024];
};