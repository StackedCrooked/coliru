#include <ctime>
#include <thread>
#include <iostream>

long long int dorands(){
  long long int a =0;
  for(int i=0; i<100000000; i++){
    a +=rand();
  }
  return a;
}

int foo(){return 0;}

int main(){
    srand(time(NULL));
  clock_t begin = clock();
  long long int e = dorands();
  clock_t end = clock();
  std::cout << "ignore: " << e << ", trial 1 time: " << end-begin << std::endl;;

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "ignore: " << e << ", trial 2 time: " << end - begin << std::endl;;

  std::thread t1(foo);
  t1.join();

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "ignore: " << e << ", trial 3 time: " << end - begin << std::endl;;

  begin = clock();
  e = dorands();
  end = clock();
  std::cout << "ignore: " << e << ", trial 4 time: " << end - begin << std::endl;;


  return 1;
}