#include <mutex>
#include <thread>
#include <vector>

class Foo{
  public:
  Foo(const std::size_t& numThreads) : buffer_(numThreads) {}

  private:
  std::vector<double> buffer_;
};

void exec(Foo&){}

int main() {
  Foo comm(10);
  std::vector<std::thread> t(10);
  for(std::size_t tid=0;tid!=10;++tid) t[tid]=std::thread(exec,std::ref(comm));
  for(std::size_t tid=0;tid!=10;++tid) t[tid].join();
}
