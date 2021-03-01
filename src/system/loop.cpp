#include <TBG/System.hpp>
#include <TBG/Exception.hpp>

tuxSystem::TuxLoop::TuxLoop()
{
    this->m_size = MAX_EVENTS;
    this->m_epoll_fd = epoll_create(MAX_EVENTS);

    if (this->m_epoll_fd == -1)
    {
        throw tuxException::TuxException("Error caught when creating an evenet loop!");
    }
}

tuxSystem::TuxLoop::TuxLoop(const size_t hint)
{
    this->m_epoll_fd = epoll_create(hint);
    this->m_size = hint;

    if (this->m_epoll_fd == -1)
    {
        throw tuxException::TuxException("Error caught when creating an evenet loop!");
    }
}

void tuxSystem::TuxLoop::loop_ctl(const int events, tuxNetwork::TuxTcpSocket *tcp_sock, size_t size)
{
    if (size > this->m_size)
    {
        char buffer[100];
        snprintf(buffer, 100, "Error caught! Size exceed, Maximum event hint size is %d!", this->m_size);

        throw tuxException::TuxException(buffer);
    }

    else if (size < this->m_size)
    {
        this->m_size = size;
    }

    this->m_events = events;

    this->m_sfd = new int[size];

    this->m_evlist = new epoll_event[size];
    epoll_event ev;

    for (int i = 0; i < size; i++)
    {
        this->m_sfd[i] = tcp_sock->get_sfd();

        ev.events = events;
        ev.data.fd = this->m_sfd[i];

        if (epoll_ctl(this->m_epoll_fd, EPOLL_CTL_ADD, this->m_sfd[i], &ev) == -1)
        {
            throw tuxException::TuxException("Error caught when adding file descriptor to an event loop");
        }
    }
}

void tuxSystem::TuxLoop::loop_launch(int (*loop_handler)(void *, void *), const int timeval)
{
    while (1)
    {
        int ready = epoll_wait(this->m_epoll_fd, this->m_evlist, this->m_size, timeval);

        if (ready == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                tuxException::TuxException("Error caught when monitoring an event loop!");
            }
        }

        for (int i = 0; i < ready; i++)
        {
            if (this->m_evlist[i].events)
            {
                if (loop_handler(reinterpret_cast<void *>(&this->m_evlist[i].events), reinterpret_cast<void *>(&this->m_evlist[i].data.fd)) == -1)
                    ;
                {
                    tuxException::TuxException("Error caught when invoking the handler!");
                }
            }
        }
    }
}