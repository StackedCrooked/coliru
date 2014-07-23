#include <string>
#include <chrono>
#include <iostream>

std::chrono::duration<double> append(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str.append("a");

  end = std::chrono::system_clock::now();
  return end - start;
};

std::chrono::duration<double> push_back(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str.push_back('a');

  end = std::chrono::system_clock::now();
  return end - start;
};

int main() {
  std::size_t size = 1000000;
  std::cerr << "append()" << std::endl;
  std::cerr << "elapsed time: " << append(size).count() << "s" << std::endl;
  std::cerr << "push_back()" << std::endl;
  std::cerr << "elapsed time: " << push_back(size).count() << "s" << std::endl;
};