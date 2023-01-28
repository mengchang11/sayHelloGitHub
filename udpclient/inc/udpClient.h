#include <arpa/inet.h>

class UdpClient {
public:
    UdpClient();
    ~UdpClient();

    // Create and start client
    int StartUdpClient();
protected:

    // Say hello to server
    int SendDataToServer();

    // Recv data
    int RecvData();
private:

    // Save client socket
    int m_udpClient;

    // Save server info
    struct sockaddr_in m_serverInfo;

    // Send data buffer
    char m_sendDataBuffer[1024];

    // Loop num
    int m_loopNum;
};