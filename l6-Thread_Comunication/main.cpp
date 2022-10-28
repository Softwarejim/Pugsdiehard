#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "wrideFunctions.h"
using namespace std;


int main(int argc, char *argv[])
{
  pthread_create(NULL, NULL, NULL, NULL);
    

    pthread_join(NULL, NULL);
    
  return 0;
}



