#include <pthread.h>
#include <iostream>
#include <unistd.h>

    void *threadFunction(void *arg){
        int *ThrId = (int*) arg;

        for (int i = 0; i < 10; i++)
        {
            sleep(1);
            std::cout << "Hallo #"<< i << " from thread: " << *ThrId << std::endl;
        }
            return NULL;         
    }

    
int main(void){

    pthread_t Thread1, Thread2;    

    int ThreadId[2] = {0, 1};    

    std::cout << "Main: Creating threads " << std::endl;
    std::cout << "Main: Waiting for threads to finish " << std::endl;

    pthread_create(&Thread1, NULL, threadFunction, static_cast<void*>(&ThreadId[0]));    
    pthread_create(&Thread2, NULL, threadFunction, static_cast<void*>(&ThreadId[1]));

    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);

    sleep(1);

    std::cout << "Main: Exiting" << std::endl;

    return 0;
    
}