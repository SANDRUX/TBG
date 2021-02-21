#include <TBG/System.hpp>

tuxSystem::TuxThread::TuxThread(void *(*func)(void * ))
{
    this->m_thread_func = func;
}

void tuxSystem::TuxThread::launch(pthread_t & tid, void * opaque)
{
    this->m_tid = tid;

    if (!pthread_create(&this->m_tid, NULL, this->m_thread_func, opaque))
    {
        throw "Error caught when creating a thread!";
    }
}

void tuxSystem::TuxThread::join(void)
{
    if (!pthread_join(this->m_tid, NULL))
    {
        throw "Error caught when waiting to the current thread!";
    }
}