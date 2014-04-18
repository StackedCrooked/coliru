#include <iostream>

#include <algorithm>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

//
// Benchmark
//
#include <sys/time.h>

#include <cstddef>

template <typename Func>
double benchmark(Func f, std::size_t iterations)
{
  f();

  timeval a, b;
  gettimeofday(&a, 0);
  for (; iterations --> 0;)
  {
    f();
  }
  gettimeofday(&b, 0);
  return (b.tv_sec * (unsigned int)1e6 + b.tv_usec) -
         (a.tv_sec * (unsigned int)1e6 + a.tv_usec);
}

//
// Solution
//
template <typename T, typename Comp>
void insert_sorted(std::vector<T>& vec, T const& e, Comp const& comp) {
    auto const it = std::lower_bound(vec.begin(), vec.end(), e, comp);

    if (it != vec.end() and not comp(e, *it)) { return; }

    vec.insert(it, e);
}

template <typename T>
void insert_sorted(std::vector<T>& vec, T const& e) {
    insert_sorted(vec, e, std::less<T>{});
}

struct VecBuffered {
    // Flush buffer into uniq, using scratch as a temporary buffer
    static void Flush(std::vector<int>& uniq, std::vector<int>& buffer, std::vector<int>& scratch) {
        std::sort(buffer.begin(), buffer.end());
        
        scratch.clear();
        scratch.reserve(uniq.size() + buffer.size());
        std::merge(uniq.begin(), uniq.end(), buffer.begin(), buffer.end(), std::back_inserter(scratch));
        
        scratch.erase(std::unique(scratch.begin(), scratch.end()), scratch.end());
        
        swap(uniq, scratch);
        buffer.clear();
    }
    
    VecBuffered(size_t& out, std::vector<int> const& stream): _out(out), _stream(stream) {}
    
    void operator()() const {
        static size_t const N = 1000;
        
        std::vector<int> uniq; uniq.reserve(N);
        std::vector<int> buffer; buffer.reserve(N);
        std::vector<int> scratch;
        
        for (int e: _stream) {
            buffer.push_back(e);
            
            if (buffer.size() >= N and buffer.size() == uniq.size()) {
                Flush(uniq, buffer, scratch);
            }
        }
        Flush(uniq, buffer, scratch);
        _out = uniq.size();
    }
    
    size_t& _out;
    std::vector<int> const& _stream;
}; // struct VecBuffered

struct VecSorter {
    VecSorter(size_t& out, std::vector<int> const& stream): _out(out), _stream(stream) {}
    
    void operator()() const {
        std::vector<int> uniq;
        for (int e: _stream) { uniq.push_back(e); }
        std::sort(uniq.begin(), uniq.end());
        uniq.erase(std::unique(uniq.begin(), uniq.end()), uniq.end());
        _out = uniq.size();
    }
    
    size_t& _out;
    std::vector<int> const& _stream;
};

int main() {
    size_t const U = 100;
    size_t const N = 1000000;
    size_t const ITERATIONS = 1;
    size_t const SAMPLES = 5;
    
    // 0. Seed with a real random value, if available
    std::random_device rd;
    std::default_random_engine engine(rd());
    
    // 1. Generate a random set of N unique values
    std::vector<int> unique_values;
    {
        std::uniform_int_distribution<int> uniform_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        while (unique_values.size() < U) {
            insert_sorted(unique_values, uniform_dist(engine));
        }
    }
    std::cout << "Generated " << unique_values.size() << " unique values in the range [" << unique_values.front() << ", " << unique_values.back() << "]\n";
    
    // 2. From that set of unique values, generate a large collection of random numbers
    std::vector<int> random_stream;
    {
        random_stream.reserve(N);
        std::uniform_int_distribution<size_t> uniform_dist(0, unique_values.size()-1);

        for (size_t i = 0; i < N; ++i) {
            random_stream.push_back(unique_values.at(uniform_dist(engine)));
        }
    }
    std::cout << "Generated a stream of " << random_stream.size() << " values\n";

    // 3. Time each solution
    double best_buff = std::numeric_limits<double>::max();
    double best_sort = std::numeric_limits<double>::max();
    
    for (size_t i = 0; i < SAMPLES; ++i) {
        size_t buff_result = 0;
        double buff = benchmark(VecBuffered{buff_result, random_stream}, ITERATIONS);
        best_buff = std::min(best_buff, buff);
        std::cout << "Buff: " << buff_result << ": " << best_buff << "\n";
         
        size_t sort_result = 0;
        double sorting = benchmark(VecSorter{sort_result, random_stream}, ITERATIONS);
        best_sort = std::min(best_sort, sorting);
        std::cout << "Sort: " << sort_result << ": " << best_sort << "\n";
    }
    
    std::cout << "Final: BUFF = " << best_buff << ", SORT = " << best_sort << "\n";


    return 0;
}