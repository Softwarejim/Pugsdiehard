#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "wrideFunctions.h"
using namespace std;

pthread_mutex_t carEntryMutex, carExitMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t entrySignal, exitSignal = PTHREAD_COND_INITIALIZER;

bool entryDoorOpen, exitDoorOpen, carWaitingEntry, carWaitingExit = false;


void* CarThreadFunc(void* CarThreadId){

        /************CAR-ENTRY********************/

    for (;;)
    {
        pthread_mutex_lock(&carEntryMutex);

        CarDrivesToEntryGarageDoor();
        carWaitingEntry = true;
        pthread_cond_signal(&entrySignal);
        while (!entryDoorOpen)
        {
        CarIsWaitingAtTheEntryGaragedoor();
        pthread_cond_wait(&entrySignal, &carEntryMutex);
        }
        CarDrivesIntoParkinglot();
        carWaitingEntry = false;
        pthread_cond_signal(&entrySignal);

        pthread_mutex_unlock(&carEntryMutex);
        sleep(1);

        /************CAR-EXIT********************/

        pthread_mutex_lock(&carExitMutex);

        CarDrivesToExitGarageDoor();
        carWaitingExit = true;
        pthread_cond_signal(&exitSignal);
        while (!exitDoorOpen)
        {
            pthread_cond_wait(&entrySignal, &carEntryMutex);
            CarIsWaitingAtTheExitGaragedoor();
        }
        CarDrivesOutOfParkinglot();
        carWaitingExit = false;
        pthread_cond_signal(&exitSignal); 

        pthread_mutex_unlock(&carExitMutex);
        sleep(1);
    }        
}

void* EntryGuardThreadFunc(void* EntGuId){
    for (;;)
    {
        pthread_mutex_lock(&carEntryMutex);
        while (!carWaitingEntry)
        {
            pthread_cond_wait(&entrySignal, &carEntryMutex);
            GaragedoorOpens();
        }
        entryDoorOpen = true;
        
        pthread_mutex_unlock(&carEntryMutex);
    }        
} 
    
void* ExitGuardThreadFunc(void*  ExiGuId){
    for (;;)
    {
        pthread_mutex_lock(&carExitMutex);
        while (!carWaitingExit)
        {
            pthread_cond_wait(&exitSignal, &carExitMutex);
            GaragedoorOpens();
        }
        exitDoorOpen = true;        
        pthread_mutex_unlock(&carExitMutex);
    }                
}
pthread_t CarThread;
pthread_t entryGuardThread;
pthread_t exitGuardThread;
int main(int argc, char *argv[])
{
  pthread_create(&CarThread, nullptr, CarThreadFunc, nullptr);
    pthread_create(&entryGuardThread, nullptr, EntryGuardThreadFunc, nullptr);
    pthread_create(&exitGuardThread, nullptr, ExitGuardThreadFunc, nullptr);

    pthread_join(CarThread, NULL);
    pthread_join(entryGuardThread, NULL);
    pthread_join(exitGuardThread, NULL);    

  return 0;
}



