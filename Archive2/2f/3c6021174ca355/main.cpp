#include <iostream>
#include <thread>
#include <chrono>
#include <future>

void work (char c) {
  for (int i = 0; i < 5; ++i) {
    (std::cout << c).flush ();
    std::this_thread::sleep_for (std::chrono::milliseconds (200));
  }
}

void not_really_async () {
  std::cout << "not_really_async:\n";
  std::async (std::launch::async, work, 'A');
  std::async (std::launch::async, work, 'B');
}

void really_async () {
  std::cout << "\n\n" << "really_async:\n";
  auto f1 = std::async (std::launch::async, work, 'A');
  auto f2 = std::async (std::launch::async, work, 'B');
}

int main () {
  not_really_async ();
  really_async ();
}