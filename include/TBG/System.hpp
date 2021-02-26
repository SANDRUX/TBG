#pragma once

#include <pthread.h>
#include <sys/epoll.h>
#include <sys/types.h> 
#include <stdio.h>     
#include <stdlib.h>                  
#include <unistd.h>    
#include <errno.h>     
#include <string.h>   
#include <stdbool.h>
#include <TBG/Network.hpp>
#include <TBG/Exception.hpp>

#define MAX_EVENTS 10

namespace tuxSystem
{
    //Thread class used by client and server 
    class TuxThread
    {
    public:

        TuxThread(void *(*)(void *));
        void launch(pthread_t &, void *);
        void join(void);
        void detach(void);
        //~TuxThread();

    private:
        void *(*m_thread_func)(void *);
        pthread_t m_tid;
    };

    //Mutex class used for TuxThread syncronisation
    class TuxMutex
    {
    public:

        TuxMutex(void);
        ~TuxMutex();
        void lock(void);
        void unlock(void);

    private:

        pthread_mutex_t m_mtx;
    };

    class TuxLoop
    {
    public:

        TuxLoop(); //opens epoll and initializes m_epoll_fd
        int loop_ctl(const int ,int *, const size_t); //event, fd array, size
        int loop_launch(tuxNetwork::TuxTcpSocket *, const int = MAX_EVENTS);

    private:

        int m_epoll_fd; //epoll file descriptor
    };
};