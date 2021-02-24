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