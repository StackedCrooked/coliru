#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

const unsigned BUFFER_SIZE = 10;

std::mutex mu;
std::condition_variable full,empty;
std::vector<int> vec;
const std::chrono::milliseconds slp(10);

auto done = false;

void produce()
{
  for (auto i = 0u; i < 2 * BUFFER_SIZE; ++i) {
    std::unique_lock<std::mutex> locker(mu);
    full.wait(locker, [] {return vec.size() < BUFFER_SIZE;});
    vec.push_back(i);
    locker.unlock();
    
    empty.notify_one();

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

  // Tell consumer we are done producing
  {
    std::lock_guard<std::mutex> lock(mu);
    done = true;
  }
  empty.notify_one();
  consumer.join();
}
