#include <array>
  using std::array;
#include <cstddef>
  using std::size_t;
#include <functional>
  using std::ref;
#include <iostream>
  using std::cout;
#include <iterator>
  using std::iterator_traits;
#include <thread>
  using std::thread;
#include <vector>
  using std::vector;
#include <random>
  using mersenne_twister = std::mt19937;

template<class T, T N>
array<T, N> series_of_numbers()
{
  array<T, N> arr;
  for(T i=0; i<N; ++i)
    arr[i] = i;
    
  return arr;
}

template<class Iterator, class Engine>
void generate_rng(Iterator begin, Iterator end, Engine& engine)
{
  std::uniform_real_distribution<double> dist;
  for(auto it = begin; it != end; ++it)
    *it = dist(engine);
}

int main()
{
  const size_t amount_of_random_numbers = 1024;
  // Engines
  const size_t Nrng = 4;
  auto seed_values = series_of_numbers<size_t, Nrng>(); // choose other seeds if you wish
  array<mersenne_twister, Nrng> engines;
  for(size_t i=0; i<Nrng; ++i)
    engines[i].seed(seed_values[i]);
  
  vector<thread> threads;
  vector<double> rngs(amount_of_random_numbers);
  
  // relevant iterators with offsets
  vector<vector<double>::iterator> begins = { rngs.begin(),
                                              rngs.begin() + amount_of_random_numbers/Nrng,
                                              rngs.begin() + 2*amount_of_random_numbers/Nrng,
                                              rngs.begin() + 3*amount_of_random_numbers/Nrng };

  vector<vector<double>::iterator> ends = { rngs.end(),
                                              rngs.end() - 3*amount_of_random_numbers/Nrng,
                                              rngs.end() - 2*amount_of_random_numbers/Nrng,
                                              rngs.end() - amount_of_random_numbers/Nrng };
  // create threads
  for(size_t n=0; n<Nrng; ++n)
    threads.emplace_back(thread(generate_rng<decltype(begins[n]), mersenne_twister>, ref(begins[n]), ref(ends[n]), ref(engines[n])));
    
  // join threads -> this is where the work will be done.
  for(size_t n=0; n<Nrng; ++n)
    threads[n].join();
    
  // rngs is filled with magical values!
  for(auto number : rngs)
    std::cout << number << '\n';
}
