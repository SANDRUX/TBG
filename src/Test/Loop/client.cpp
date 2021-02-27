#include <TBG/System.hpp>
#include <TBG/Network.hpp>
#include <TBG/Exception.hpp>
#include <TBG/Player.hpp>

int main()
{
    std::string ip;
    int port;

    std::cin >> ip;
    std::cin >> port;

    try
    {
        tuxNetwork::TuxTcpSocket obj;
        obj.connect(ip, port);

        tuxSystem::TuxLoop loop(1);

        loop.loop_ctl(EPOLLIN, &obj, 1);

        loop.loop_launch([](void *events, void *sfd) -> int 
        {    
            int buffer[2];

            if (*reinterpret_cast<int *>(events) == EPOLLIN)
            {
                if (read(*reinterpret_cast<int *>(sfd), buffer, sizeof(buffer)) == -1)
                {
                    std::cerr << "Could not read the data!" << std::endl;
                    return -1;
                }

                std::cout << buffer[0] << " " << buffer[1] << std::endl;
            }
        }, 0);
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}