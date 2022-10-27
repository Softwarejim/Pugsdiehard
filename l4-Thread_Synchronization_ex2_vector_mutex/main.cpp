#include "Vector.hpp"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

Vector vector;
pthread_mutex_t mutex;
 
void *writer(void * threadId)
{
  bool err;
  while (1)
  {
    pthread_mutex_lock(&mutex);
    err = vector.setAndTest((long)threadId);
    pthread_mutex_unlock(&mutex);

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
    int NTHREADS = 1;

    cout << "Angiv, hvor mange gange programmet skal køre" << endl;
    cin >> NTHREADS; 
       

    if (0 < NTHREADS && NTHREADS <= 100)
    {      
      pthread_t threads[NTHREADS];
      pthread_mutex_init(&mutex, nullptr);
      
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
