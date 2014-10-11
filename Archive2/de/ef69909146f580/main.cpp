#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <algorithm>

class Timer {
  std::chrono::high_resolution_clock::time_point begin;
  std::chrono::high_resolution_clock::time_point end;
  public:
    Timer() : begin(std::chrono::high_resolution_clock::now()), end() {}
    void start() { begin = std::chrono::high_resolution_clock::now(); }
    void stop() { end = std::chrono::high_resolution_clock::now(); }
    float read() { std::chrono::duration<float> time = end - begin; return time.count(); }
};

int func(size_t index) {
  // return some function of the index
  return index * index / 1000;
}

struct MyGenerator {
  size_t index{0};

  int operator()() { return func(index++); }
};

void approach1(size_t size) {
  std::vector<int> A;
  A.reserve(size);
  for (size_t i = 0; i != size; ++i)
    A.push_back(func(i));
}

void approach2(size_t size) {
  std::vector<int> A(size);
  for (size_t i = 0; i != size; ++i)
    A[i] = func(i);
}

void approach3(size_t size) {
  std::vector<int> A(size);
  MyGenerator mg;
  std::generate(A.begin(), A.end(), mg); 
}

float test(const size_t size, const int repeat, std::function<void(size_t)> func) {
    Timer timer;
  for (int i = 0; i != repeat; ++i)
    func(size);
  timer.stop();
  return timer.read();
}

int main() {
  const size_t size = 10000;
  const int repeat = 1000;
  
  // Compare approaches to fill a vector
  std::cout << "Approach 1: " << test(size, repeat, approach1) << "\n";
  std::cout << "Approach 2: " << test(size, repeat, approach2) << "\n"; 
  std::cout << "Approach 3: " << test(size, repeat, approach3) << "\n"; 
}
