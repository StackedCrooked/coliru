#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

void produce()
{
  for (auto i = 0u; i < 2 * BUFFER_SIZE; ++i) {
    std::unique_lock<std::mutex> locker(mu);
    full.wait(locker, [] {return vec.size() < BUFFER_SIZE;});
    auto was_empty = vec.empty();
    vec.push_back(i);
    locker.unlock();

    if (was_empty()) {
        empty.notify_one();
    }

    std::this_thread::sleep_for(slp);
  }
}

void consume()
{
  for (;;) {
    std::unique_lock<std::mutex> locker(mu);
    while (vec.empty()) {
      if (done) {
        return;
      }
      empty.wait(locker);
    }

    auto value = vec.back();
    vec.pop_back();
    locker.unlock();

    full.notify_one();
    std::cout << "Consumed: " << value << '\n';
  }
}

int main() {
  vec.reserve(BUFFER_SIZE*2);
  std::thread producer(produce), consumer(consume);
  producer.join();
  
  // Produce some more
  producer = std::thread(produce);
  producer.join();

  // Produce A LOT more
  std::vector<std::thread> many_producers(8);
  for (auto&& t : many_producers) {
      t = std::thread(produce);
  }
  for (auto && t : many_producers) {
      t.join();
  }

  // Tell consumer we are done producing
  {
    std::lock_guard<std::mutex> lock(mu);
    done = true;
  }
  empty.notify_one();
  consumer.join();
}
