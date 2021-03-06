#include <TBG/Network.hpp>
#include <TBG/Exception.hpp>

tuxNetwork::TuxTcpSocket::TuxTcpSocket(void)
{
    this->m_sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (m_sfd == -1)
    {
        throw tuxException::TuxException("Error caught when creating a socket!");
    }
}

tuxNetwork::TuxTcpSocket::TuxTcpSocket(const int c_sfd)
{
    this->m_sfd = c_sfd;
}

tuxNetwork::TuxTcpSocket::~TuxTcpSocket()
{
    if (close(this->m_sfd))
    {
        std::cerr << "Could not close the socket, Error occurred or already closed!" << std::endl;
    }
}

void tuxNetwork::TuxTcpSocket::connect(const std::string & ip, const int portNum)
{
    sockaddr_in * addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNum);

    inet_aton(ip.c_str(), &addr->sin_addr);

    int status = ::connect(this->m_sfd, (struct sockaddr *)addr, sizeof(sockaddr));

    if (status == -1)
    {
       throw tuxException::TuxException("Error caught when connecting to a socket!");
    }
}

size_t tuxNetwork::TuxTcpSocket::send(const std::vector<uint8_t>& buf, size_t size)
{
    size_t numWrite = write(this->m_sfd, buf.data(), size);

    if (numWrite == -1)
    {
        std::cerr << "Error caught when sending the data!" << std::endl;
        return -1;
    }
    
    else if (!numWrite)
    {
        if (close(this->m_sfd))
        {
            std::cerr << "Error caught when closing the socket!" << std::endl;
            return 0;
        }
    }

    return numWrite;
}

size_t tuxNetwork::TuxTcpSocket::receive(std::vector<uint8_t> &buf, size_t size)
{
    buf.clear();

    uint8_t temp[size];

    size_t numRead = read(this->m_sfd, temp, size);

    for (int i = 0; i < (int)size; i++)
    {
        buf.push_back(temp[i]);
    }

    if (numRead == -1)
    {
        std::cerr << "Error caught when receiving the data!" << std::endl;
        return -1;
    }

    else if (!numRead)
    {
        if (close(this->m_sfd))
        {
            std::cerr << "Error caught when closing the socket!" << std::endl;
            return 0;
        }
    }

    return numRead;
}

tuxNetwork::TuxListener::TuxListener(const std::string & ip, const int portNum)
{
    sockaddr_in *addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNum);

    inet_aton(ip.c_str(), &addr->sin_addr);

    this->m_sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (m_sfd == -1)
    {
        throw tuxException::TuxException("Error caught when creating a socket!");
    }
    
    if (bind(this->m_sfd, (sockaddr *)addr, sizeof(sockaddr)))
    {
        throw tuxException::TuxException("Error caught when binding a socket!");
        close(m_sfd);
    }

    if (listen(this->m_sfd, MAX_QUEUED_REQUESTS) == -1)
    {
        throw tuxException::TuxException("Error caught when setting socket as listener!");
        close(m_sfd);
    }
}

tuxNetwork::TuxListener::~TuxListener()
{
    if (close(this->m_sfd))
    {
        std::cerr << "Error caught when closing the socket!" << std::endl;
    }
}

tuxNetwork::TuxTcpSocket tuxNetwork::TuxListener::accept(void)
{
    int l_cfd = ::accept(this->m_sfd, NULL, NULL);

    if (l_cfd == -1)
    {
        throw tuxException::TuxException("Error caught when accepting a request!");
    }
    
    return tuxNetwork::TuxTcpSocket(l_cfd);
}