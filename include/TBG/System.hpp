#pragma once

#include <pthread.h>

namespace tuxSystem
{
    class TuxThread
    {
    public:

        TuxThread(void *(*)(void *));
        void launch(pthread_t &, void *);
        void join(void);
        //~TuxThread();

    private:
        void *(*m_thread_func)(void *);
        pthread_t m_tid;
    };
};