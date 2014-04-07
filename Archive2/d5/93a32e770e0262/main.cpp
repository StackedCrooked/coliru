#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS     5

void* printString(void *x)
{
    cout << (char*)x << endl;
        pthread_exit(NULL);
}

int main ()
{
     pthread_t threads[NUM_THREADS];
     int i;
     string temp = "hello";

  char *bufferG;
  bufferG = new char[temp.size() + 1]; 
  std::copy(temp.begin(), temp.end(), bufferG); 
  bufferG[temp.size()] = '\0'; 
  cout << bufferG << endl;
  
     for( i=0; i < NUM_THREADS; i++ ){
         cout << "main() : creating thread, " << i << endl;
         pthread_create(&threads[i], NULL, printString,  bufferG ); //(void *) &bufferG also doesn't work
     }
 pthread_exit(NULL);
 }
 
