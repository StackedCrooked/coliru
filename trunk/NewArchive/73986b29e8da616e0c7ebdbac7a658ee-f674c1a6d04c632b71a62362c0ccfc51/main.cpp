#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

class chrono_timer // minimal timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

    public:

    chrono_timer ( ) : m_start(std::chrono::high_resolution_clock::now()) { }

    void reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
    void delay(std::size_t duration)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }
    std::size_t elapsed_us() // must call reset() after a call to this method
    {
        return std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::high_resolution_clock::now() - m_start).count();
    }
};

//------------------------------------------------------------------------------

typedef std::uint64_t Width_t;
typedef std::minstd_rand Rng_t;
typedef std::uniform_int_distribution<std::size_t> Eng_t;

struct IncrementFill {
    std::size_t i;
    IncrementFill ( ) : i(0) { }
    std::size_t operator()() { return i++; }
};

//------------------------------------------------------------------------------

class Bs2 : public boost::signals2::trackable
{
    std::size_t m_data[4];

    public:

    static std::size_t s_sum;

    void method_one(Rng_t&) const;
    void method_two(std::size_t, Rng_t&);

    static void s_function_one(Rng_t&);
    static void s_function_two(std::size_t, Rng_t&);
};

std::size_t Bs2::s_sum = 123456791;

void Bs2::method_one(Rng_t& rng) const
{
    volatile std::size_t a = rng();
    (void)a;
}
void Bs2::method_two(std::size_t a, Rng_t& rng)
{
    s_sum ^= rng() * a;
}
void Bs2::s_function_one(Rng_t& rng)
{
    volatile std::size_t a = rng();
    (void)a;
}
void Bs2::s_function_two(std::size_t a, Rng_t& rng)
{
    s_sum ^= rng() * a;
}

//------------------------------------------------------------------------------

void bs2_benchmark()
{
    Rng_t rng;
    Eng_t eng (0, 100);
    chrono_timer timer;

    boost::signals2::signal<void(Rng_t&)> signal_one;
    boost::signals2::signal<void(std::size_t, Rng_t&)> signal_two;

    for (std::size_t N = 16; N <= 128; N *= 2) // magic numbers are actually globals
    {
        Width_t previous_sum = 1;
        Width_t current_sum = 2;
        Width_t sum_count = 0;

        while (previous_sum < current_sum && sum_count < 100) // magic number actually g_max_count
        {
            std::vector<std::size_t> random_index(N);
            std::generate(random_index.begin(), random_index.end(), IncrementFill());
            std::shuffle(random_index.begin(), random_index.end(), rng);
        
            previous_sum = current_sum;
            timer.delay(10);
            timer.reset();
            {
                std::vector<Bs2> obj(N);
                for (std::size_t index : random_index)
                {
                    if (eng(rng) > 50) // magic number actually g_emit_ratio
                    {
                        Bs2* ptr = &obj[index];
                        signal_one.connect(boost::bind(&Bs2::method_one, ptr, _1));
                        signal_two.connect(boost::bind(&Bs2::method_two, ptr, _1, _2));
                    }
                    else
                    {
                        signal_one(rng);
                        signal_two(index, rng);
                    }
                }
            }
            current_sum += timer.elapsed_us();
            ++sum_count;
        }
        double elapsed_ms = (previous_sum / (double)sum_count) * 0.001;
        std::cout << (N / elapsed_ms) << std::endl;
    }
}

int main()
{
    bs2_benchmark();
}
