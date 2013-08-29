#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

class chrono_timer // minimal timer class
{
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

    public:

    chrono_timer() : m_start(std::chrono::high_resolution_clock::now()) {}

    void reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }
    template <typename T>
    void delay(std::size_t duration)
    {
        std::this_thread::sleep_for(T(duration));
    }
    template <typename T>
    std::size_t count()
    {
        return std::chrono::duration_cast<T>
            (std::chrono::high_resolution_clock::now() - m_start).count();
    }
};

//------------------------------------------------------------------------------

chrono_timer g_timer;
std::size_t g_start_n = 16;
std::size_t g_maximum_n = 128;
std::size_t g_maximum_count = 8;
std::size_t g_emission_ratio = 50;

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

    void method_one(Rng_t& rng) const __attribute__ ((noinline))
    {
        volatile std::size_t a = rng();
        (void)a;
    }
    void method_two(std::size_t a, Rng_t& rng) __attribute__ ((noinline))
    {
        s_sum ^= rng();
        (void)a;
    }
};

std::size_t Bs2::s_sum = 123456791;

//------------------------------------------------------------------------------

void bs2_benchmark()
{
    Rng_t rng;
    Eng_t eng (0, 100);

    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::microseconds;
    using std::chrono::duration_cast;

    boost::signals2::signal<void(Rng_t&)> signal_one;
    boost::signals2::signal<void(std::size_t, Rng_t&)> signal_two;

    for (std::size_t N = g_start_n; N <= g_maximum_n; N *= 2)
    {
        Width_t sum_previous = 1;
        Width_t sum_current = 2;
        Width_t sum_count = 0;

        // loop until wrap around occurs or until maximum count is reached
        while (sum_previous < sum_current && sum_count < g_maximum_count)
        {
            // try to randomize access patterns
            std::vector<std::size_t> random_index (N);
            std::generate(random_index.begin(), random_index.end(), IncrementFill());
            std::shuffle(random_index.begin(), random_index.end(), rng);

            // delay seems to increase timing accuracy
            g_timer.delay<milliseconds>(10);
            sum_previous = sum_current;
            g_timer.reset();
            {
                // time boost::signals2::trackable construction overhead
                std::vector<Bs2> obj (N);

                for (std::size_t index : random_index)
                {
                    // what is the next operation? connection or emission
                    if (eng(rng) > g_emission_ratio)
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
                // time boost::signals2::trackable destruction overhead
            }
            sum_current += g_timer.count<microseconds>();
            sum_count += 1;
        }
        double elapsed_ms = duration_cast<duration<double, std::milli>>
            (microseconds(sum_previous / sum_count)).count();

        std::cout << (N / elapsed_ms) << std::endl;
    }
    std::cout << Bs2::s_sum << std::endl;
}

int main()
{
    bs2_benchmark();
}
