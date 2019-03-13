// Author:     Hermit
// CreateTime: Mar 13, 2019 11:32 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include "Thread.h"
namespace thread
{

Thread::Thread(ThreadCallback cb) : cb_(cb) {

}

void* run(void *p) {
    Thread *ptr = reinterpret_cast<Thread*>(p); 
    ptr->cb_();
}

void Thread::start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(NULL, &attr, run, (void*)this);
}
} // end of namespace thread
