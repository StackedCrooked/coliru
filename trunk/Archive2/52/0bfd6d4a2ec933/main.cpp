#include <future>
#include <thread>
#include <vector>

class Foo{
  public:
  Foo(const std::size_t& numThreads) : buffer_(numThreads) {}

  private:
  std::vector<double> buffer_;
};

void exec(Foo&){}

Foo job(const unsigned n_threads) {
  Foo comm(n_threads);
  std::vector<std::thread> t(n_threads - 1);
  for (auto& th : t) {
    th = std::thread(exec, std::ref(comm));
  }
  exec(comm);
  for (auto& th : t) {
    th.join();
  }
  return comm;
}

int main() {
  std::future<Foo> f = std::async(std::launch::async, job, 10);
  f.get();
}
