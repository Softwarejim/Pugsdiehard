#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <pthread.h>
#include "ScopedLocker.hpp"
using namespace std;

class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {   
         pthread_mutex_init(&mut_,nullptr);  

         vector_ = new int[size_];
         set(0);
      }

   ~Vector()
      {
         delete[] vector_;
      }

   bool setAndTest(int n)
      {
         ScopedLocker s(mut_);
         set(n);
         return test(n);
      }

private:
   void set(int n)
      {
         for(unsigned int i=0; i<size_; i++) vector_[i] = n;
      }

   bool test(int n)
      {
         for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
         return true;
      }

   int*           vector_;
   unsigned int   size_;
   pthread_mutex_t mut_;
};

#endif
