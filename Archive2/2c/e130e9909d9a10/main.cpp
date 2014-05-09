#include <vector>
#include <boost/algorithm/string/join.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/format.hpp>
#include <string>
#include <chrono>

class Timer
{
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point _start;
public:
    Timer() { reset(); }
    void reset() { _start = now(); }
    double elapsed()
    {
        using namespace std::chrono;
        auto e = now() - _start;
        return duration_cast<nanoseconds>(e).count()*1.0e-9;
    }
    clock::time_point now()
    {
        return clock::now();
    }
};

struct B
{ 
      typedef boost::shared_ptr<const B> ConstPtr;
      std::string string1() const { return std::to_string(rand()); }
      std::string string2() const { return std::to_string(rand()); }
};

struct A
{
      /***code***/
      std::vector<B::ConstPtr> sharedPtrList;
      std::string boostJoinAndFormat() const {
          return boost::algorithm::join( sharedPtrList | boost::adaptors::transformed( 
                      [](B::ConstPtr obj )->std::string
                      { 
                        return ( boost::format( "%s:%s" ) % obj->string1() % obj->string2() ).str(); 
                      } ),
                  ",");
      }
      std::string stringStream() const {
          std::ostringstream os;
          for(auto& b : sharedPtrList)
              os << b->string1() << ':' << b->string2() << ',';

          auto s = os.str();
          if (!s.empty())
              s.resize(s.size()-1);
          return s; // moves
      }

      std::string boostKarma() const {
          if (sharedPtrList.empty())
              return {};

          std::string result;
          result.reserve(40 * sharedPtrList.size()); // average length preallocate?

          auto out = back_inserter(result);

          namespace k =  boost::spirit::karma;
          for(auto& b : sharedPtrList)
              k::generate(out, k::string << ':' << k::string << ',', b->string1(), b->string2());

          result.resize(result.size()-1);
          return result; // moves
      }
};

#include <iostream>

int main()
{
    A a;
    std::generate_n(back_inserter(a.sharedPtrList), 100, [] { return boost::make_shared<B>(); });

    auto const iterations = 1ul<<15;

    {
        volatile auto x = 0ull;
        Timer sw;
        for (size_t i = 0; i < iterations; ++i) x += a.boostJoinAndFormat().size();

        std::cout << x << " in " << sw.elapsed() << "s\n";
    }

    {
        volatile auto x = 0ull;
        Timer sw;
        for (size_t i = 0; i < iterations; ++i) x += a.stringStream().size();

        std::cout << x << " in " << sw.elapsed() << "s\n";
    }

    {
        volatile auto x = 0ull;
        Timer sw;
        for (size_t i = 0; i < iterations; ++i) x += a.boostKarma().size();

        std::cout << x << " in " << sw.elapsed() << "s\n";
    }

}
