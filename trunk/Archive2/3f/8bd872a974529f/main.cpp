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

int foo(){return 0;}

int main(){
  clock_t begin = clock();
  volatile int e = dorands();
  clock_t end = clock();
  std::cout << "trial 1 time: " << end-begin << std::endl;;

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "trial 2 time: " << end-begin << std::endl;;

  std::thread t1(foo);
  t1.join();

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "trial 3 time: " << end-begin << std::endl;;

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "trial 4 time: " << end-begin << std::endl;;


  return 1;
}