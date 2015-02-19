#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

int dorands(){
  int a =0;
  for(int i=0; i<1000000; i++){
    a +=rand();
  }
  return a;
}
std::chrono::microseconds dotest() {
  auto begin = std::chrono::high_resolution_clock::now();
  volatile int e = dorands();
  auto end = std::chrono::high_resolution_clock::now();
  (void)e;
  std::chrono::microseconds dur = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  return dur;
}
void dotests() {
    std::chrono::microseconds times[20];
    for(int i=0; i<20; ++i) 
        times[i] = dotest();
    std::sort(begin(times), end(times));
    std::cout << "TestSet min: " << times[0].count() << "ms\n";
}

int foo(){return 0;}

int main(){
    dotests();
    {
        std::thread t1(foo);
        t1.join();
        dotests();
    }
    dotests();
    return 1;
}