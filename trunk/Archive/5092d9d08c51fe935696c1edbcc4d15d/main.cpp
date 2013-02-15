#include <iostream>
#include <thread>

template<class T, typename... Args>
void show_stuff(Args... a)
{
    std::array<T, sizeof...(Args)> arr = { a... };

	std::cout<<arr[1]<<endl;
}

int main()
{
    show_stuff<int>(4, 5, 6);
    
    show_stuff<float>(3, 1, "g");
}