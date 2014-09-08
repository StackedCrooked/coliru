#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstring>





struct Timer
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;

    TimePoint m_start, m_finish;
    std::string m_msg;
    std::ostream& m_os;

    Timer(std::string msg, std::ostream& os) 
        : m_start(Clock::now())
        , m_msg(std::move(msg))
        , m_os(os)        
    {
    }

    ~Timer()
    {
        using namespace std::chrono;
        m_finish = Clock::now();

        char buf[512] = { '\0' };
        sprintf(buf, "%s,took:%0.3lf secs\n", m_msg.c_str(), (duration_cast<milliseconds>(m_finish - m_start).count()) / 1000.0);
        m_os.write(buf, strlen(buf));
    }

    Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
};


template<typename Func>
auto TimeTaken(Func&& f, std::string msg) -> decltype(f())
{
    std::cout << "auto TimeTaken(Func&& f, std::string msg) -> decltype(f())\n";
    Timer t(std::move(msg), std::cout);
    return f();
}


template<typename Func, typename ...Args>
auto TimeTaken(Func&& f, std::string msg, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
{
    std::cout << "auto TimeTaken(Func&& f, std::string msg, Args const&... args) -> decltype(f(args...))\n";
    Timer t(std::move(msg), std::cout);
    return f(std::forward<Args>(args)...);
}

std::string bar()
{

	std::cout << "bar()\n";

    auto IsPrime = [](int x)
    {
        bool prime = true;
        if ((x >= 0 && x <= 2) || x % 2 == 0)
            return prime;

        for (int i = 3; i <= x / 2; i += 2)
        {
            if (x / i == 0)
                return prime;
        }
        return !prime;
    };


	int count = 0;
	int start = 0, finish = 100;
    

	for (; start < finish; ++start){
		count += IsPrime(start) ? 1 : 0;
	}

	return std::to_string(count) 
		   + " primes between " 
		   + std::to_string(start) 
		   + " and " 
		   + std::to_string(finish) + "\n";
}


void foo(int x, std::string msg)
{
    std::cout << "foo(" << x << "," << msg << ")\n";
}


int main()
{
    TimeTaken([]{
		std::cout << "Hello\n";
    }, "Saying Hello");

    TimeTaken(foo, "calling foo with 1 and \"Hey Jagan\"", 1, "Hey Jagan");
    std::cout << TimeTaken(bar, "calling bar");

    std::cin.ignore();
}

