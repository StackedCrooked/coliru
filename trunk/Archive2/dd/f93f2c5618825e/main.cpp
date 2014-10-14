#include <chrono>
#include <iostream>
using namespace std::chrono;

int main()
{
  const auto begin = high_resolution_clock::now();
  std::cout << "Hello world!\n";
  auto time = high_resolution_clock::now() - begin;
  std::cout << "Elapsed time: " << duration<double, std::milli>(time).count() << ".\n";
}