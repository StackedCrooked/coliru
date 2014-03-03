#include <queue>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <atomic>

#define CONSUMERS 1
#define PRODUCERS 1



typedef std::queue<size_t> queue_type;
const int iterations = 100;
queue_type queue;

std::atomic_bool done (false);
int producer_count = 0;
std::atomic_int consumer_count (0);

void producer(void)
{
    for (int i = 0; i != iterations; ++i) {
        int value = ++producer_count;
        queue.push(value);
    }
}

void consumer(void)
{
    int value;
    while (!done) {
        while (!queue.empty()) {
            std::cout << queue.front() << std::endl;
            queue.pop();
            ++consumer_count;
        }
        std::this_thread::yield();
    }

    while (!queue.empty()) {
        std::cout << queue.front() << std::endl;
        queue.pop();
        ++consumer_count;
    }
}

int main() {

    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    done = true;
    consumer_thread.join();
  return 0;
}
