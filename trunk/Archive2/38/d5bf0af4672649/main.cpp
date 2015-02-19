#include <chrono>
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
    auto begin = std::chrono::high_resolution_clock::now();
  volatile int e = dorands();
    auto end = std::chrono::high_resolution_clock::now();
  std::cout << "trial time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;;
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