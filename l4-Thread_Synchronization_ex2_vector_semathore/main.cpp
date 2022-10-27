#include "Vector.hpp"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
Vector vector;
sem_t semathore;
 
void *writer(void * threadId)
{
  bool err;
  while (1)
  { 
    sem_wait(&semathore);   
    err = vector.setAndTest((long)threadId);
    sem_post(&semathore);    

    if (err == false)
    {
        cout << "FEJL I: " <<(long)threadId << endl;        
    }
    sleep(1);
  }
  return nullptr;
}


int main(int argc, char *argv[])
{
  sem_init(&semathore, 0,1);
    int NTHREADS = 1;

    cout << "Angiv, hvor mange gange programmet skal køre" << endl;
    cin >> NTHREADS; 
       

    if (0 < NTHREADS && NTHREADS <= 100)
    {      
      pthread_t threads[NTHREADS];      
      
      cout << "Creating " << NTHREADS << " thread(s)" << endl;

      for (int i = 1; i <= NTHREADS; i++)
      {
        pthread_create(&threads[i], nullptr, writer, static_cast<void*>(&vector));
        cout << "Creating thread: " << i << endl; 
      sleep(1);
      }      

      for (int i = 0; i < NTHREADS; i++)
      {
        pthread_join(threads[i], nullptr);
      }
    }  

  return 0;
}


/*https://condor.depaul.edu/glancast/443class/docs/pthreads.html*/
