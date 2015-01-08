// Console2013.cpp : Defines the entry point for the console application.
//




#include <chrono>
#include <iostream>
#include <string>
#include <cstring>
#include <memory>

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
	Timer t(std::move(msg), std::cout);
	return f();
}


template<typename Func, typename ...Args>
auto TimeTaken(Func&& f, std::string msg, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
{

	Timer t(std::move(msg), std::cout);
	return f(std::forward<Args>(args)...);
}





int main(int argc, char** argv)
{
	auto pixel_ptr = std::make_unique<int[]>(307200);
	int someCalculatedVal = 10;
	
	TimeTaken([&]{

		for (int i = 0; i < 307200; i++){
			pixel_ptr[i] = someCalculatedVal;
		}
	}, "Time taken");


	std::cout << pixel_ptr[0] << "\n";
	std::cin.ignore();
	return 0;
}





