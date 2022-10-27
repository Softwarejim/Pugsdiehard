#include <iostream>
#include <pthread.h>
#include <string>
using namespace std;

void *threadFunc(void *arg){
    cout << "Hello world!" << endl;
    return arg;
}

int main(){
    pthread_t time;

    pthread_create(&time, NULL, threadFunc, NULL);
    pthread_join(time, NULL);
    
    return 0;
}