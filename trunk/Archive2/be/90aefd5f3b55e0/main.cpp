#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <atomic>
#include <random>
#include <array>

void update_cur_best(std::atomic<int>& best, int a, int b) {
  if (a < b) {
    a = b;
  }
  
  auto cur_best = best.load(std::memory_order_relaxed);
  while (cur_best < a && !best.compare_exchange_weak(cur_best, a))
    ;
}

void run(int max, std::atomic<int>& best) {
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(0, max);
    
  for(int i = 0; i < 15; ++i) {
    update_cur_best(best, distribution(generator), distribution(generator));
  }
}

//g++ -std=c++0x -pthread px.cpp -o px
int main()
{
  std::atomic<int> best{0};
  const int max = 100;
  std::array<std::thread, 3> threads;
  
  for (auto& t : threads) {
      t = std::thread(run, max, std::ref(best));
  }

  for (auto& t : threads) {
      t.join();
  }

  std::cout << "best = " << best << std::endl;
}
