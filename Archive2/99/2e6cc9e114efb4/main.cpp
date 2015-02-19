#include <ctime>
#include <thread>
#include <iostream>

int dorands(){
  int a =0;
  for(int i=0; i<1000000; i++){
    a +=rand();
  }
  return a;
}
void dotests() {
  clock_t begin = clock();
  volatile int e = dorands();
  clock_t end = clock();
  std::cout << "trial time: " << end-begin << std::endl;;
}

int foo(){return 0;}

int main(){
    dotests();
    dotests();
    dotests();
    dotests();
    dotests();
    dotests();

    {
        std::thread t1(foo);
        t1.join();
        
        
        dotests();
        dotests();
        dotests();
        dotests();
        dotests();
        dotests();
    }
    
    dotests();
    dotests();
    dotests();
    dotests();
    dotests();


  return 1;
}