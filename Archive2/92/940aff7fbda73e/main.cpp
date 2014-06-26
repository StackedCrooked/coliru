#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <condition_variable>
#define BUFFER_SIZE 10

std::mutex mu;
std::condition_variable full,empty;
std::vector<int> vec;
int i=0;
int num_consumed=0;
std::chrono::milliseconds slp(100);

void produce()
{
  while (i < 2*BUFFER_SIZE) {
    std::unique_lock<std::mutex> locker(mu);
    full.wait(locker, [] {return vec.size() != BUFFER_SIZE;});
    vec.push_back(i++);
    locker.unlock();
    empty.notify_one();
    std::this_thread::sleep_for(slp);
  }
}

void consume()
{
  while(1){ //(!vec.empty()) {        // <---- vec.empty() would cause deadlock.                                                                                           
    std::unique_lock<std::mutex> locker(mu);
    empty.wait(locker, [] {return !vec.empty();});
    std::cout << "Consumed:" << vec.back() <<"\n";
    vec.pop_back();
    ++num_consumed;
    if (num_consumed ==  2*BUFFER_SIZE) return;
    locker.unlock();
    full.notify_one();
    std::this_thread::sleep_for(slp);
  }
}

int main() {
  vec.reserve(BUFFER_SIZE);
  std::thread producer(produce), consumer(consume);
  producer.join();
  consumer.join();
  return 0;
}