#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>

class timer
{
    using Clock = std::chrono::high_resolution_clock;
    using milliseconds = std::chrono::milliseconds;

public:
    timer() { t0 = Clock::now(); }

    milliseconds elapsed_ms() const {
        return std::chrono::duration_cast<milliseconds>(Clock::now() - t0);
    }

private:
    Clock::time_point t0;
};

template <int NUM_ELEMS>
void benchmark()
{
    const int reps = 10000;
    std::chrono::milliseconds ms_qa, ms_vi, ms_qa2;

    {
        timer t2;

        std::vector<int> vi;
        for (int i = 0; i < reps; ++i) 
        {
            vi.clear();
            // vi.reserve(NUM_ELEMS);

            for (int ii = 0; ii < NUM_ELEMS; ++ii) {
                vi.emplace_back(ii << 2);
            }

            for (int i = 0; i < 1000; ++i)
            {
                auto n = vi.at(rand() % NUM_ELEMS);
            }
        }

        ms_vi = t2.elapsed_ms();
    }

    {
        timer t1;



        ms_qa = t1.elapsed_ms();
    }

    {
        timer t1a;



        ms_qa2 = t1a.elapsed_ms();
    }

    std::stringstream ss;
    
    ss << NUM_ELEMS << ": ";
    //ss << "QA: " << ms_qa.count() << " ms , ";
    //ss << "QA2: " << ms_qa2.count() << " ms, ";
    ss << "vec: " << ms_vi.count() << " ms";
    
    auto s = ss.str();
    
    std::cout << s << std::endl;
}

int main()
{
    benchmark<8>();
    benchmark<16>();
    benchmark<32>();
    benchmark<64>();
    benchmark<128>();
    benchmark<256>();
    benchmark<512>();
    benchmark<1024>();
    benchmark<2048>();
    benchmark<4096>();
    benchmark<8192>();
}
