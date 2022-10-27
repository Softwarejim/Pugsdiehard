#include <pthread.h>
#include <unistd.h>
using namespace std;

class ScopedLocker
{
public:
    ScopedLocker(pthread_mutex_t &mtx)
     : mtx_local(&mtx)
    {
        pthread_mutex_lock(mtx_local);
    }

    ~ScopedLocker()
    {
        pthread_mutex_unlock(mtx_local);
    }

private:
    pthread_mutex_t * mtx_local;
};

//Call by vlue vs call by reference
//https://www.youtube.com/watch?v=HEiPxjVR8CU


