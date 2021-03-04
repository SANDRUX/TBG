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
        void cancel(void);
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

        TuxLoop(const size_t); //opens epoll and initializes m_epoll_fd
        TuxLoop();
        void loop_ctl(const int ,tuxNetwork::TuxTcpSocket *, const size_t); //event, fd array, size
        void loop_launch(int (*)(void *, void *), const int);

    private:

        int m_epoll_fd; //epoll file descriptor
        int m_size = 0;
        int * m_sfd;
        int m_events;
        epoll_event * m_evlist;
    };
};