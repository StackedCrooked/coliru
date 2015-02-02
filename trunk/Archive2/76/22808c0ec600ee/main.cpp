#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

    class SyncAction
	{
	public:
		std::mutex m;

	public:        
        template<typename F>
		auto Execute(F f) -> decltype(f())
		{
			std::lock_guard<std::mutex> lock(m);
			return f();
		}
	};
    
SyncAction a;

    
void f1()
{
    std::cout<<"thread #"<<std::this_thread::get_id()<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout<<"thread #"<<std::this_thread::get_id()<<" completed"<<std::endl;
}

typename std::thread::id f2()
{
    f1();
    return std::this_thread::get_id();
}

void worker()
{
    a.Execute(f1);
}


int main()
{
    std::cout<<"startup thread #"<<std::this_thread::get_id()<<std::endl;
    
    std::thread t(worker);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto i = a.Execute(f2);
  
  a.Execute([](){});
  
    std::cout<<"res is "<<i<<std::endl;
  
    t.join();
    return 0;
}
