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
        tuxNetwork::TuxListener obj(ip, port);
        tuxNetwork::TuxTcpSocket client = obj.accept();

        tuxSystem::TuxLoop loop(1);

        loop.loop_ctl(EPOLLOUT, &client, 1);

        loop.loop_launch([](void *events, void *sfd) -> int {
            int buffer[2] = {1, 2};

            if (*reinterpret_cast<int *>(events) == EPOLLOUT)
            {
                if (write(*reinterpret_cast<int *>(sfd), buffer, sizeof(buffer)) == -1)
                {
                    std::cerr << "Could not write the data!" << std::endl;
                    return -1;
                }
            }
            return 0;
        }, 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}