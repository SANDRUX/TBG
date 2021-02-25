#include <TBG/Network.hpp>
#include <TBG/System.hpp>
#include <TBG/Player.hpp>
#include <vector>
#include <iostream>

std::vector<tuxNetwork::TuxTcpSocket> client;

void * accept_request(void * arg)
{
    tuxNetwork::TuxListener * server =  reinterpret_cast<tuxNetwork::TuxListener *>(arg);

    while (1)
    {
        try 
        {
            client.push_back(server->accept());
        }
        catch(const std::exception & e)
        {
            std::cerr << e.what();
            pthread_exit(NULL);
        }
    }
}

int main()
{
    std::string IP;
    int PORT;

    std::cout << "Enter Server IP: " << std::endl;
    std::cin >> IP;
    std::cout << "Enter Server PORT: " << std::endl;
    std::cin >> PORT;

    try
    {
        tuxNetwork::TuxListener Listener(IP, PORT);

        pthread_t tId;

        tuxSystem::TuxThread server_thread(accept_request);
        server_thread.launch(tId, &Listener);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    std::vector<uint8_t> data;

    while (client[0].receive(data, 2) != -1 || client[0].receive(data, 2) != 0)
    {
        std::cout << data[0] << " " << data[1] << std::endl;
    }

    return 0;
}