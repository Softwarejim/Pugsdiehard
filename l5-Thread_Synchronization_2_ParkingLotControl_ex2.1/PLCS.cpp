#include <pthread.h>
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

void* EntryGuardThread(void* EntGuId){
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
    
void* ExitGuardThread(void*  ExiGuId){
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



