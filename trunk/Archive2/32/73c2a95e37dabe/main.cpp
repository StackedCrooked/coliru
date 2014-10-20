#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <cstdio>
#include <vector>

std::mutex mt;
static int iMem = 0;
int maxITr = 10;

void renum()
{
    // Ensure that only 1 task will update the variable
    std::lock_guard<std::mutex> l(mt);
    int tmpMem = iMem;
    usleep(10); // Make the system sleep/induce delay
    iMem = tmpMem + 1;
    printf("iMem = %d\n", iMem);
}

int main()
{
  std::vector<std::thread> mths;
  mths.reserve(maxITr);
  for (int i = 0; i < maxITr; i++) {
    mths.emplace_back(renum);
  }
  for (auto& mth : mths) {
    mth.join();
  }
}
