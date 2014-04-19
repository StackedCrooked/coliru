#include <cassert>

#include <iostream>

#include <algorithm>
#include <limits>
#include <random>
#include <unordered_set>
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

struct UnorderedSet {
    UnorderedSet(size_t& out, std::vector<int> const& stream):
        _out(out), _stream(stream) {}
    
    void operator()() const {
        std::unordered_set<int> set;
        for (int e: _stream) { set.insert(e); }
        _out = set.size();
    }
    
    size_t& _out;
    std::vector<int> const& _stream;
}; // struct UnorderedSet

struct HashOpenAddressing {
    template <typename T, typename Hasher = std::hash<T>>
    class HashTable: Hasher {
    public:
        HashTable(size_t const estimate, double loadFactor):
            _elements(GetPrimeBySize(estimate, loadFactor)), _size(0), _seenDefault(false) {}

        HashTable(size_t const estimate, double loadFactor, Hasher const& hasher):
            Hasher(hasher), _elements(GetPrimeBySize(estimate, loadFactor)), _size(0), _seenDefault(false) {}

        size_t size() const { return _seenDefault + _size; }

        void add(T const& e) {
            static T const Default = T{};

            if (e == Default) { _seenDefault = true; return; }

            Hasher const& hasher = *this;
            size_t const hash = hasher(e);

            size_t const prime = _elements.size();
            size_t const original = hash % prime;

            size_t pos = original;
            do {
                if (_elements[pos] == e) { return; }

                if (_elements[pos] == Default) { _elements[pos] = e; ++_size; return; }

                pos += 1; pos %= prime;
            } while (pos != original);

            assert(0 && "Oopsie!");
        } // add

    private:
        static size_t GetPrime(size_t i) {
            static size_t const Primes[] = { 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 1646237 };
            static size_t const Size = sizeof(Primes) / sizeof(Primes[0]);

            assert(i < Size && "No Prime for this index");

            return Primes[i];
        }

        static size_t GetPrimeBySize(size_t const estimate, double loadFactor) {
          for (size_t i = 0; ; ++i) {
            if (GetPrime(i) >= loadFactor * estimate) { return GetPrime(i); }
          }
          return 0;
        }

        std::vector<T> _elements;
        size_t _size;
        bool _seenDefault;
    }; // class HashTable

    HashOpenAddressing(size_t& out, size_t const estimate, double loadFactor, std::vector<int> const& stream):
        _out(out), _estimate(estimate), _loadFactor(loadFactor), _stream(stream) {}
    
    void operator()() const {
        HashTable<int> set{_estimate, _loadFactor};
        for (int e: _stream) { set.add(e); }
        _out = set.size();
    }
    
    size_t& _out;
    size_t const _estimate;
    double const _loadFactor;
    std::vector<int> const& _stream;
}; // HashOpenAddressing

struct VecPusher {
    VecPusher(size_t& out, std::vector<int> const& stream):
        _out(out), _stream(stream) {}
    
    void operator()() const {
        std::vector<int> vec; vec.reserve(_stream.size());
        for (int e: _stream) { vec.push_back(e); }
        _out = vec.size();
    }
    
    size_t& _out;
    std::vector<int> const& _stream;
}; // struct VecPusher

struct VecUniquerReserver {
    VecUniquerReserver(size_t& out, size_t const estimate, std::vector<int> const& stream): _out(out), _estimate(estimate), _stream(stream) {}
    
    void operator()() const {
        std::vector<int> uniq; uniq.reserve(_estimate);
        for (int e: _stream) { insert_sorted(uniq, e); }
        _out = uniq.size();
    }
    
    size_t& _out;
    size_t const _estimate;
    std::vector<int> const& _stream;
}; // struct VecUniquerReserver

struct VecUniquer {
    VecUniquer(size_t& out, std::vector<int> const& stream): _out(out), _stream(stream) {}
    
    void operator()() const {
        std::vector<int> uniq;
        for (int e: _stream) { insert_sorted(uniq, e); }
        _out = uniq.size();
    }
    
    size_t& _out;
    std::vector<int> const& _stream;
}; // struct VecUniquer

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
    size_t const N = 100000;
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
    double best_uset = std::numeric_limits<double>::max();
    double best_open = std::numeric_limits<double>::max();
    double best_push = std::numeric_limits<double>::max();
    double best_ures = std::numeric_limits<double>::max();
    double best_uniq = std::numeric_limits<double>::max();
    double best_sort = std::numeric_limits<double>::max();
    
    for (size_t i = 0; i < SAMPLES; ++i) {
        size_t result = 0;

        double uset = benchmark(UnorderedSet{result, random_stream}, ITERATIONS);
        best_uset = std::min(best_uset, uset);
        std::cout << "Uset: " << result << ": " << best_uset << "\n";
    
        double open = benchmark(HashOpenAddressing{result, U, 8.0, random_stream}, ITERATIONS);
        best_open = std::min(best_open, open);
        std::cout << "Open: " << result << ": " << best_open << "\n";

        double push = benchmark(VecPusher{result, random_stream}, ITERATIONS);
        best_push= std::min(best_push, push);
        std::cout << "Push: " << result << ": " << best_push << "\n";

        /*
        double ures = benchmark(VecUniquerReserver{result, U, random_stream}, ITERATIONS);
        best_ures = std::min(best_ures, ures);
        std::cout << "Ures: " << result << ": " << best_ures << "\n";
        
        double uniq = benchmark(VecUniquer{result, random_stream}, ITERATIONS);
        best_uniq = std::min(best_uniq, uniq);
        std::cout << "Uniq: " << result << ": " << best_uniq << "\n";
        */
        
        double sorting = benchmark(VecSorter{result, random_stream}, ITERATIONS);
        best_sort = std::min(best_sort, sorting);
        std::cout << "Sort: " << result << ": " << best_sort << "\n";
    }
    
    std::cout << "Final: USET = " << best_uset << ", OPEN = " << best_open << ", PUSH = " << best_push << ", URES = " << best_ures << ", UNIQ = " << best_uniq << ", SORT = " << best_sort << "\n";


    return 0;
}

