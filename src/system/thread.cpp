#include <TBG/System.hpp>
#include <TBG/Exception.hpp>

tuxSystem::TuxThread::TuxThread(void *(*func)(void * ))
{
    this->m_thread_func = func;
}

void tuxSystem::TuxThread::launch(pthread_t & tid, void * opaque)
{
    this->m_tid = tid;

    if (!pthread_create(&this->m_tid, NULL, this->m_thread_func, opaque))
    {
        throw tuxException::TuxException("Error caught when creating a thread!");
    }
}

void tuxSystem::TuxThread::join(void)
{
    if (!pthread_join(this->m_tid, NULL))
    {
        throw tuxException::TuxException("Error caught when waiting to the current thread!");
    }
}

void tuxSystem::TuxThread::detach(void)
{
    if (!pthread_detach(this->m_tid))
    {
        throw tuxException::TuxException("Error caught when detaching this thread!");
    }  
} 

tuxSystem::TuxMutex::TuxMutex(void)
{
    this->m_mtx = PTHREAD_MUTEX_INITIALIZER;
}

void tuxSystem::TuxMutex::lock(void)
{
    if (pthread_mutex_lock(&this->m_mtx))
    {
        throw tuxException::TuxException("Error caught when locking the mutex!");
    }
}

void tuxSystem::TuxMutex::unlock(void)
{
    if (pthread_mutex_unlock(&this->m_mtx))
    {
        throw tuxException::TuxException("Error caught when unlocking the mutex!");
    }
}

tuxSystem::TuxMutex::~TuxMutex(void)
{
    if (pthread_mutex_destroy(&this->m_mtx))
    {
        std::cerr << "Error caught in Destructor when destroying the mutex!" << std::endl;
    }
}

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

void tuxSystem::TuxLoop::loop_ctl(const int events, tuxNetwork::TuxTcpSocket * tcp_sock, size_t size)
{
    if (size > this->m_size)
    {
        char buffer[100];
        snprintf(buffer, 100, "Error caught! Size exceed, Maximum event hint size is %d!", this->m_size);
    
        throw tuxException::TuxException(buffer);
    }

    else if(size < this->m_size) 
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

void tuxSystem::TuxLoop::loop_launch(int (*loop_handler)(void *, void *),const int timeval)
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
                if (loop_handler(reinterpret_cast<void *>(&this->m_evlist[i].events), reinterpret_cast<void *>(&this->m_evlist[i].data.fd)) == -1);
                {
                    tuxException::TuxException("Error caught when invoking the handler!");
                }
            }
        }
    }
}