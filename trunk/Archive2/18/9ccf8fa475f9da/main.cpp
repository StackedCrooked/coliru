#include <iostream>
#include <vector>
#include <chrono>
#include <set>
#include <random>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename F, typename... Ts>
void
benchmark (std::string const& name, std::size_t times, F f, Ts&&... args) 
{
  using hrc = std::chrono::high_resolution_clock;
  using  ms = std::chrono::milliseconds;
  using       std::chrono::duration_cast;

  auto start = hrc::now ();

  for (std::size_t i = 0; i < times; ++i) {
    f (std::forward<Ts> (args)...);
  }

  auto end      = hrc::now ();
  auto duration = duration_cast<ms> (end - start);

  std::cout << std::left << std::setw (20) << name;
  std::cout << ": " << duration.count () << "ms\n";
}

int
main (int argc, char *argv[])
{
  std::size_t TESTS = 10000;

  std::set<int> set1, set2;

  std::default_random_engine         engine (0xDEADBEEF);
  std::uniform_int_distribution<int> dist   (0,1000);

  for (int i = 0; i < 10000; ++i) {
    set1.insert (dist (engine));
    set2.insert (dist (engine));
  }

  benchmark ("naive-insert", TESTS, [&]{
    std::set<int> result (set1);
    result.insert (set2.begin (), set2.end ());
  });

  benchmark ("set_union", TESTS, [&]{
    std::set<int> result (set1);

    std::set_union (
      result.begin (), result.end (),
      set2  .begin (), set2  .end (),
      std::inserter (result, result.end ())
    );
  });
}