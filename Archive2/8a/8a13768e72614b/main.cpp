#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <numeric>
#include <sstream>

typedef std::chrono::high_resolution_clock hclock;
typedef std::chrono::duration<float, std::milli> ms;

template<typename F>
void time(const std::string& message, F f, unsigned int n = 100)
{
    std::vector<float> times;
    hclock::time_point t_0, t_1;
    for(unsigned int i = 0; i < n; i++)
    {
        t_0 = hclock::now();
        f();
        t_1 = hclock::now();
        times.push_back(ms(t_1 - t_0).count());
    }
    float average = float(std::accumulate(times.begin(), times.end(), 0.0f)) / float(times.size());
    std::cout << message << ": " << average << "ms\n";
}

int main ()
{
    const unsigned int N = 30000;
    const std::string s1 = " Test str ";
    std::string str;

    time("(str) operator+", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
            str = s1 + "Test data2" + "Test data3";
    });

    time("(str) operator+=", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            str = s1;
            str += "Test data2";
            str += "Test data3";
        }
    });

    time("(str) append", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            str = s1;
            str.append("Test data2");
            str.append("Test data3");
        }
    });

    time("(str) stringstream", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            std::ostringstream oss;
            oss << s1;
            oss << "Test data2";
            oss << "Test data3";
            str = oss.str();
        }
    });

    time("(int) operator+", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
            str = s1 + std::to_string(i) + "Test data3";
    });

    time("(int) operator+=", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            str = s1;
            str += std::to_string(i);
            str += "Test data3";
        }
    });

    time("(int) append", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            str = s1;
            str.append(std::to_string(i));
            str.append("Test data3");
        }
    });

    time("(int) stringstream", [&]()
    {
        for(unsigned int i = 0; i < N; i++)
        {
            std::ostringstream oss;
            oss << s1;
            oss << i;
            oss << "Test data3";
            str = oss.str();
        }
    });
}