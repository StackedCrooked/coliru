#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

int dorands(){
  int a =0;
  for(int i=0; i<1000000; i++){
    a +=rand();
  }
  return a;
}

int foo(){return 0;}

int main(){
  auto begin = std::chrono::high_resolution_clock::now();
  volatile int e = dorands();
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "trial 1 time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;;

  begin = std::chrono::high_resolution_clock::now();
  e = dorands();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "trial 2 time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;;

  std::thread t1(foo);
  t1.join();

  begin = std::chrono::high_resolution_clock::now();
  e = dorands();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "trial 3 time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;;

  begin = std::chrono::high_resolution_clock::now();
  e = dorands();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "trial 4 time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;;


  return 0;
}