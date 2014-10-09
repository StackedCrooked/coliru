#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <functional>

class Timer {
  std::chrono::high_resolution_clock::time_point begin;
  std::chrono::high_resolution_clock::time_point end;
  public:
    Timer() : begin(std::chrono::high_resolution_clock::now()), end() {}
    void start() { begin = std::chrono::high_resolution_clock::now(); }
    void stop() { end = std::chrono::high_resolution_clock::now(); }
    float read() { std::chrono::duration<float> time = end - begin; return time.count(); }
};

void approach1(const std::vector<int>& A, const std::vector<int>& B) {
  std::vector<int> AB;
  AB.reserve( A.size() + B.size() );
  AB.insert( AB.end(), A.begin(), A.end() );
  AB.insert( AB.end(), B.begin(), B.end() );
}

void approach2(const std::vector<int>& A, const std::vector<int>& B) {
  std::vector<int> AB ( A.begin(), A.end() );
  AB.insert ( AB.end(), B.begin(), B.end() );
}

void approach3(const std::vector<int>& A, const std::vector<int>& B) {
  std::vector<int> AB(A.size() + B.size());
  std::copy(A.begin(), A.end(), AB.begin());
  std::copy(B.begin(), B.end(), AB.begin() + B.size());
}

float test(const size_t size, const int repeat, std::function<void(const std::vector<int>& A, const std::vector<int>& B)> func) {
  std::vector<int> A(size);
  std::vector<int> B(size);
  std::iota(A.begin(), A.end(), 0); 
  std::iota(B.begin(), B.end(), size);
  
  Timer timer;
  for (int i = 0; i != repeat; ++i)
    func(A, B);
  timer.stop();
  return timer.read();
}

int main() {
  const size_t size = 1000;
  const int repeat = 10000;
  std::cout << "Approach 1: " << test(size, repeat, approach1) << "\n";
  std::cout << "Approach 2: " << test(size, repeat, approach2) << "\n";
  std::cout << "Approach 3: " << test(size, repeat, approach3) << "\n";
}
