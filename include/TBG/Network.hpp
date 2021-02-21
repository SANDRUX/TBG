#pragma once

#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <string>

#define MAX_QUEUED_REQUESTS 128

namespace tuxNetwork
{
    class TuxTcpSocket
    {
    public:
        TuxTcpSocket(void);
        TuxTcpSocket(const int);
        ~TuxTcpSocket();
        int connect(const std::string &, const int);
        size_t send(const std::vector<uint8_t> &, size_t);
        size_t receive(std::vector<uint8_t> &, size_t);

    private:
        int m_sfd;
    };

    class TuxListener
    {
    public:
        TuxListener(const std::string &, const int);
        ~TuxListener();
        TuxTcpSocket accept(void);

    private:
        int m_sfd;
    };
};
