// Author:     Hermit
// CreateTime: Mar 13, 2019 11:20 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#pragma once
#include <pthread.h>
#include <functional>
namespace thread
{
class Thread {
public:
    typedef std::function<void()> ThreadCallback;
    Thread(ThreadCallback cb);
    void start();
    ThreadCallback cb_;
};
void* run(void *);
}// end of namespace thread
