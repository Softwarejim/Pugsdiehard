#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>

    unsigned int shared = 0;

    void *threadIncFunction(void *arg){
        int* ThrId = static_cast<int*> (arg);

        while(1){

            std::cout << "Thread" << *ThrId << ": in action. shared is: " << shared << std::endl;
            sleep(1);
            shared++;
        }                    
            return NULL;         
    }

    void *threadPrintFunction(void *arg){

        int* ThrId = static_cast<int*> (arg);

        while(1){

            sleep(1);
            std::cout << "Thread" << *ThrId <<" Says: Shared is now: "<< shared << std::endl;
        }
            return NULL;         
    }

    
int main(void){

    int valueInc, valueRead;

    valueInc = 1;
    valueRead = 2;

    pthread_t Incrementer, Reader;   

    pthread_create(&Incrementer, NULL, threadPrintFunction, &valueInc);    
    pthread_create(&Reader, NULL, threadIncFunction, &valueRead);

    pthread_join(Incrementer, NULL);
    pthread_join(Reader, NULL);

    sleep(1);

    std::cout << "Main: Exiting" << std::endl;

    return 0;
    
}