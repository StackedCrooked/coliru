#include <chrono>
#include <iostream>
#include <random>

class timer
{
public:
  timer() : start_(std::chrono::steady_clock::now()) {}

  double elapsed() const
  {
    return static_cast<double>(
      std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start_).count());
  }

private:
  std::chrono::steady_clock::time_point start_;
};

template<class rnd_t, class test>
void do_single_test(const char* rngname, const char* testname, test func) 
{
  const int num_tests = 1000000;
  std::random_device rd{};
  rnd_t rnd{rd()};

  unsigned dummy(0);
  timer measure;
  for (unsigned i(0); i < 1000000; ++i)
      dummy += (unsigned)func(rnd, 0, 1000000);
  const double elapsed(measure.elapsed());  
  std::cout<<rngname<<"+"<<testname;
  std::cout<<" found "<<dummy;
  std::cout<<" over "<<num_tests;
  std::cout<<" in "<<(elapsed/1000.0)<<"s";
  std::cout<<" (avg "<<(elapsed/num_tests*1000.0)<<"ns)";
  std::cout<<std::endl;
}

template<class rnd_t>
void do_tests(const char* rngname) 
{
    std::uniform_int_distribution<> int_dist{};
    typedef decltype(int_dist)::param_type iparm_t; 
    std::uniform_real_distribution<> real_dist{};
    typedef decltype(real_dist)::param_type rparm_t;
    //all parameters captured by value, none by reference.  keeps tests independent
    do_single_test<rnd_t>(rngname, "raw        ", [](rnd_t rnd, int min, int max) mutable {return rnd();});
    do_single_test<rnd_t>(rngname, "intbetween ", [int_dist](rnd_t rnd, int min, int max) mutable {return int_dist(rnd, iparm_t(min,max-1));});
    do_single_test<rnd_t>(rngname, "realbetween", [real_dist](rnd_t rnd, int min, int max) mutable {return real_dist(rnd, rparm_t(min,max-1));});
}

int main()
{
    do_tests<std::mt19937_64>("mt19937_64");
    do_tests<std::mt19937   >("mt19937   ");

  return 0;
}