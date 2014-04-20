#include <boost/pool/pool_alloc.hpp>
#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
//#include <gc/gc_allocator.h>

using string = std::string;

namespace patch {
    template <typename T> string to_string(const T& in) {
        return boost::lexical_cast<string>(in);
    }
}

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


class Garbage {
    public:
        std::vector<string> outer;
        std::vector<string> old;
        const int nThreads = 1;

        void go() {
            outer.resize(1000000);
            //old.reserve(1000000);
            Timer timer;

            for (int i = 0; i < 10; ++i) {
                if (i % 100 == 0) {
                    std::cout << "DOING AN OLD" << std::endl;
                    doOld();
                }

                for (int j = 0; j < 1000000/nThreads; ++j)
                    outer.push_back(patch::to_string(j));

                outer.clear();
                std::cout << timer.elapsed() << std::endl;
                timer.reset();
            }
        }

        void doOld() {
            old.clear();
            for (int i = 0; i < 1000000/nThreads; ++i)
                old.push_back(patch::to_string(i));
        }
};

int main() {
    Garbage().go();
}
