#include <array>
#include <atomic>
#include <cassert>
#include <thread>

class spinning_barrier
{
    public:
        spinning_barrier (unsigned int threadCount) :
            threadCnt(threadCount),
            step(0),
            waitCnt(0)
        {}

        bool wait()
        {
            if(waitCnt.fetch_add(1) >= threadCnt - 1)
            {
                std::lock_guard<std::mutex> lock(mutex);
                step += 1;

                condVar.notify_all();
                waitCnt.store(0);
                return true;
            }
            else
            {
                std::unique_lock<std::mutex> lock(mutex);
                unsigned char s = step;

                condVar.wait(lock, [&]{return step == s;});
                return false;
            }
        }
    private:
        const unsigned int threadCnt;
        unsigned char step;

        std::atomic<unsigned int> waitCnt;
        std::condition_variable condVar;
        std::mutex mutex;
};

int main() {
  static const std::size_t n_iterations = 20000000;
  static const std::size_t n_threads = 2;
  spinning_barrier barrier{n_threads};
  auto spin = [&barrier]{
    for(std::size_t count = 0; count < n_iterations; ++count)
      barrier.wait();
    };
  std::array<std::thread,n_threads - 1> threads;
  for (auto&& t : threads) {
    t = std::thread{spin};
  }
  spin();
  for (auto&& t : threads) {
    t.join();
  }
}
