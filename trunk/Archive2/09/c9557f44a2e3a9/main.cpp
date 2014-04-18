#include <array>
#include <atomic>
#include <cassert>
#include <thread>

class spinning_barrier
{
public:
    spinning_barrier (unsigned int n) : n_ (n), nwait_ (0), step_(0) {}

    bool wait ()
    {
        unsigned int step = step_.load ();

        if (nwait_.fetch_add (1) == n_ - 1)
        {
            /* OK, last thread to come.  */
            nwait_.store (0); // XXX: maybe can use relaxed ordering here ??
            step_.fetch_add (1);
            return true;
        }
        else
        {
            /* Run in circles and scream like a little girl.  */
            while (step_.load () == step)
                ;
            return false;
        }
    }

protected:
    /* Number of synchronized threads. */
    const unsigned int n_;

    /* Number of threads currently spinning.  */
    std::atomic<unsigned int> nwait_;

    /* Number of barrier syncronizations completed so far, 
     * it's OK to wrap.  */
    std::atomic<unsigned int> step_;
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
