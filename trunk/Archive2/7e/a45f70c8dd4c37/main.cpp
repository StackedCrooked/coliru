#include <thread>

struct foo
{
  void init(int, long) {}
};

template <typename ... Args>
std::thread init_threaded(foo *sample, Args && ... args)
{
  auto func = [=]()
  {
    sample->init(args...);
  };

  return std::thread(func);
}

int main()
{
  foo f;
  auto t = init_threaded(&f, 10, 20L);
  t.join();
}
