#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented
    {
      static std::mutex io_mutex;
      std::lock_guard<std::mutex> lk(io_mutex);
      std::cout << "local pointer in a thread:\n"
                << "  lp.get() = " << lp.get()
                << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
int main()
{
    std::shared_ptr<int> t1;
    std::shared_ptr<int> t;
    t1 = t;
    t = std::make_shared<int>();
}