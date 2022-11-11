#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "wrideFunctions.h"
using namespace std;

pthread_mutex_t carEntryMutex;
pthread_mutex_t carExitMutex;
pthread_mutex_t ExitOrrcupMutex;
pthread_mutex_t EntryOrrcupMutex;                

pthread_cond_t entrySignal;
pthread_cond_t exitSignal; 
pthread_cond_t entryOccuSignal; 
pthread_cond_t exitOccuSignal; 

void* CarThreadFunc(void* id){  

    string* CarThreadId = (string*) id;
    for (;;)
    {
        pthread_mutex_lock(&carEntryMutex); // LOCK!

        while (entryOrccupied){
          pthread_cond_wait(&entryOccuSignal, &carEntryMutex);
        }        

        CarDrivesToEntryGarageDoor(CarThreadId);        
        pthread_cond_signal(&entrySignal);

        while (!entryDoorOpen){
          pthread_cond_wait(&entrySignal, &carEntryMutex);
        }       
        
        CarDrivesIntoParkinglot(CarThreadId);
        pthread_cond_signal(&entrySignal);

        while (entryDoorOpen){
          pthread_cond_wait(&entrySignal, &carEntryMutex);
        }

        CarIsParktInParkinglot(CarThreadId);
        pthread_cond_broadcast(&entryOccuSignal);
        sleep((rand() % 5 + 1)); 
        pthread_mutex_unlock(&carEntryMutex); // UNLOCK!           

        /////////////// EXIT ///////////////////////////
        
        pthread_mutex_lock(&carExitMutex); // LOCK

        while (exitOrccupied){
          pthread_cond_wait(&exitOccuSignal, &carExitMutex);
        }
        
        CarDrivesToExitGarageDoor(CarThreadId);
        pthread_cond_signal(&exitSignal);

        while (!exitDoorOpen){
          pthread_cond_wait(&exitSignal, &carExitMutex);
          }        

        CarDrivesOutOfParkinglot(CarThreadId);
        pthread_cond_signal(&exitSignal); 

        while (exitDoorOpen)
          pthread_cond_wait(&exitSignal, &carExitMutex);        

        CarIsWaitingOutside(CarThreadId);
        pthread_cond_broadcast(&exitOccuSignal);
        sleep((rand() % 5 + 1));
        pthread_mutex_unlock(&carExitMutex);
    } 
    pthread_exit(NULL);       
}

void* EntryGuardThreadFunc(void* EntGuId){
    for (;;)
    {
        pthread_mutex_lock(&carEntryMutex); // LOLCK

        while (!carWaitingEntry){
          pthread_cond_wait(&entrySignal, &carEntryMutex);  
          }         

          EntryGaragedoorOpens();
          pthread_cond_broadcast(&entrySignal); 

        while (carWaitingEntry){
          pthread_cond_wait(&entrySignal, &carEntryMutex); 
          }        

          EntryGaragedoorClosses();
          pthread_cond_broadcast(&entrySignal);                
          pthread_mutex_unlock(&carEntryMutex); // UNLOCK
    } 
      pthread_exit(NULL);       
} 
    
void* ExitGuardThreadFunc(void*  ExiGuId){
    for (;;)
    {
        pthread_mutex_lock(&carExitMutex); // LOCK

        while (!carWaitingExit){
          pthread_cond_wait(&exitSignal, &carExitMutex);
          }        

        ExitGaragedoorOpens();
        pthread_cond_broadcast(&exitSignal); 

        while (carWaitingExit){
          pthread_cond_wait(&exitSignal, &carExitMutex);     
        }
        ExitGaragedoorClosses();
        pthread_cond_broadcast(&exitSignal);
        pthread_mutex_unlock(&carExitMutex); // UNLOCK
    } 
    pthread_exit(NULL);               
}

int main(int argc, char *argv[])
{
  srand (time(NULL));
  const int NUMBERCars = 4;

  pthread_t entryGuardThread;
  pthread_t exitGuardThread;
  pthread_t CarsThread[NUMBERCars];
  string carID[NUMBERCars] = {"Peugot", "Volvo", "Tesla", "Renault"};
  
  pthread_mutex_init(&carEntryMutex, NULL);
  pthread_mutex_init(&carExitMutex, NULL);
  pthread_cond_init(&entrySignal, NULL);
  pthread_cond_init(&exitSignal, NULL);

  for (int i = 0; i < NUMBERCars; i++)
  {
      pthread_create(&CarsThread[i], nullptr, CarThreadFunc, static_cast <void*>(&carID[i]));
  }
  
  pthread_create(&entryGuardThread, nullptr, EntryGuardThreadFunc, nullptr);
  pthread_create(&exitGuardThread, nullptr, ExitGuardThreadFunc, nullptr);

  for (int i = 0; i < NUMBERCars; i++)
  {
        pthread_join(CarsThread[i], NULL);
  }

  pthread_join(entryGuardThread, NULL);
  pthread_join(exitGuardThread, NULL);    

  return 0;
}



