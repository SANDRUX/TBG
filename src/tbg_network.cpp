#include <tbg_network.hpp>

tuxNetwork::TuxTcpSocket::TuxTcpSocket()
{
    this->sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1)
    {
        std::cerr << "Error caught when creating a socket!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

tuxNetwork::TuxTcpSocket::~TuxTcpSocket()
{
    if (close(this->sfd))
    {
        std::cerr << "Error caught when closing the socket!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void tuxNetwork::TuxTcpSocket::connect(const std::string & ip, const int portNum)
{
    sockaddr_in * addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNum);

    inet_aton(ip.c_str(), &addr->sin_addr);

    int status = ::connect(this->sfd, (struct sockaddr *)addr, sizeof(sockaddr));

    if (status == -1)
    {
        throw "Error caught when connecting to a socket!";
    }
}

size_t tuxNetwork::TuxTcpSocket::send(std::vector<uint8_t>& buf, size_t size)
{
    size_t numWrite = write(this->sfd, buf.data(), size);

    if (numWrite == -1)
    {
        throw "Error caught when sending the data!";
        return -1;
    }

    return numWrite;
}

size_t tuxNetwork::TuxTcpSocket::receive(std::vector<uint8_t> &buf, size_t size)
{
    size_t numRead = read(this->sfd, buf.data(), size);

    if (numRead == -1)
    {
        throw "Error caught when receiving the data!";
        return -1;
    }

    return numRead;
}

tuxNetwork::TuxListener::TuxListener(const std::string & ip, const int portNum)
{
    sockaddr_in *addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNum);

    inet_aton(ip.c_str(), &addr->sin_addr);

    this->sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1)
    {
        std::cerr << "Error caught when creating a socket!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (bind(this->sfd, (sockaddr *)addr, sizeof(sockaddr)))
    {
        std::cerr << "Error caught when binding a socket!";
        exit(EXIT_FAILURE);
    }

    if (listen(this->sfd, MAX_QUEUED_REQUESTS) == -1)
    {
        std::cerr << "Error caught when setting socket as listener!";
        exit(EXIT_FAILURE);
    }
}

tuxNetwork::TuxListener::~TuxListener()
{
    //TODO
}

tuxNetwork::TuxTcpSocket & tuxNetwork::TuxListener::accept()
{
    this->cfd = ::accept(this->sfd, NULL, NULL);

    if (this->cfd == -1)
    {
        std::cerr << "Error caught when accepting a request!";
        exit(EXIT_FAILURE);
    }

    // tuxNetwork::TuxTcpSocket::TuxTcpSocket obj;

    //TODO

    // return obj;
}