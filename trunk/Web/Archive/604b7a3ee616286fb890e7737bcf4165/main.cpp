#include <iostream>
#include <thread>

template<class T, typename... Args>
void show_stuff(Args... a)
{
    std::array<T, sizeof...(Args)> arr = { a... };

	cout<<arr[1]<<endl;
}

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}