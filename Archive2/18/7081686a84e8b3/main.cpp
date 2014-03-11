#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

class Timer
{
public:
    Timer();
	void Start();
	void Stop();
	void Restart();
	double GetTimePassed();
private:
	typedef std::chrono::time_point<std::chrono::system_clock> SystemClock;

	SystemClock begin;
	SystemClock end;

	bool isCounting;
};
Timer::Timer() : isCounting(false)
{
}

void Timer::Start()
{
    begin = std::chrono::system_clock::now();
	isCounting = true;
}

void Timer::Stop()
{
	end = std::chrono::system_clock::now();
	isCounting = false;
}

void Timer::Restart()
{
	begin = std::chrono::system_clock::now();
	isCounting = true;
}

double Timer::GetTimePassed()
{
	if(isCounting) {
		SystemClock now = std::chrono::system_clock::now();
		return ((std::chrono::duration<double, std::milli>)(now - begin)).count();
	}
	else {
		return ((std::chrono::duration<double, std::milli>)(end - begin)).count();
	}
}

int main()
{
    std::srand(std::time(0));
    std::vector<int> a;
    std::vector<int> b;
    std::vector<int> c;
    std::vector<int> d;
    for(int i = 0; i < 121; i++)
    {
        a.push_back(std::rand());
        b.push_back(std::rand());
        c.push_back(std::rand());
        d.push_back(std::rand());
    }
    Timer ta;
    Timer tb;
    Timer tc;
    Timer td;
    ta.Start();
    std::sort(a.begin(), a.end());
    ta.Stop();
    tb.Start();
    std::stable_sort(b.begin(), b.end());
    tb.Stop();
    tc.Start();
    std::partial_sort(a.begin(), a.end(), a.end());
    tc.Stop();
    td.Start();
    std::nth_element(a.begin(), a.end() + a.size()/2, a.end());
    td.Stop();
    
    std::cout << "Sorting an vector of " << a.size() << " elements" << std::endl;
    std::cout << "std::sort         : " << ta.GetTimePassed() << "ms" << std::endl;
    std::cout << "std::stable_sort  : " << tb.GetTimePassed() << "ms" << std::endl;
    std::cout << "std::partial_sort : " << tc.GetTimePassed() << "ms" << std::endl;
    std::cout << "std::nth_element  : " << td.GetTimePassed() << "ms" << std::endl;
}
