// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mm;           // mutex for critical section
std::mutex nn;
void printStart(int n) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  std::lock_guard<std::mutex> lock(mm);
  for (int i=0; i<n; ++i) { if(i==1000){lock.std::lock_guard<std::mutex>::~lock_guard();}std::cout <<"*"; }
  std::cout << '\n';
}
void printAmpersand( int n){
    std::lock_guard<std::mutex> lock(mm);
    for (int i=0; i<n; ++i) { if(i==1000){lock.std::lock_guard<std::mutex>::~lock_guard();}std::cout <<"&"; }
  std::cout << '\n';
}

int main ()
{
  std::thread th1 (printStart,300);
  std::thread th2 (printAmpersand,300);

  th1.join();
  th2.join();

  return 0;
}