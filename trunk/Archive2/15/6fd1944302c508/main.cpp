#include <algorithm>
#include <array>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

namespace {
constexpr std::array<double, 100> p = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

template<size_t index, bool isZero>
struct DotProductCalculator
{
    static double Calculate(const std::vector<double>& xArg)
    {
        return (xArg[index] * p[index])
            + DotProductCalculator<index - 1, p[index - 1] == 0.0>::Calculate(xArg);
    }
};

template<>
struct DotProductCalculator<0, true>
{
    static double Calculate(const std::vector<double>&)
    {
        return 0.0;
    }
};

template<>
struct DotProductCalculator<0, false>
{
    static double Calculate(const std::vector<double>& xArg)
    {
        return xArg[0] * p[0];
    }
};

template<size_t index>
struct DotProductCalculator<index, true>
{
    static double Calculate(const std::vector<double>& xArg)
    {
        return 0.0 + DotProductCalculator<index - 1, p[index - 1] == 0.0>::Calculate(xArg);
    }
};

template<typename ArrayType>
double f_p_driver(const std::vector<double>& xArg, const ArrayType&)
{
     return DotProductCalculator<std::tuple_size<ArrayType>::value - 1,
                            p[std::tuple_size<ArrayType>::value -1] == 0.0>::Calculate(xArg);
}

template <typename Array1, typename Array2>
auto f_stdlib(const Array1& x, const Array2& p) -> decltype(x[0] * p[0]) {
  // assert(x.size() >= p.size());
  return std::inner_product(std::begin(x), std::begin(x) + p.size(),
                            std::begin(p), decltype(x[0] * p[0]){0});
}

class timer {
  typedef std::chrono::high_resolution_clock hrc;
  hrc::time_point start = hrc::now();
public:
  template <typename T=hrc::duration>
  T elapsed() const { return std::chrono::duration_cast<T>(hrc::now() - start); }
};

template <typename F>
void time_n_runs(unsigned long long N, const char* name, F&& f) {
  std::cout << name << ": Result: " << f() << ", ";
  auto sum = decltype(f()){0};
  timer t;
  while(--N > 0) {
    sum += f();
  }
  std::cout << "Sum: " << sum << ", Elapsed: "
            << t.elapsed<std::chrono::microseconds>().count() << " us\n";
}
} // anonymous namespace

int main() {
  const auto N = (1ULL << 24);

  std::mt19937 engine(std::time(nullptr));
  std::uniform_real_distribution<double> dist(0, 10);
  auto rng = [&]{ return dist(engine); };

  std::vector<double> x;
  std::generate_n(std::back_inserter(x), 100, rng);

  time_n_runs(N, "f_p_driver", [&]{ return f_p_driver(x, p); });
  time_n_runs(N, "f_stdlib", [&]{ return f_stdlib(x, p); });
}
