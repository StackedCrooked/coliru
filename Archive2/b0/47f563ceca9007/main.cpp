// VS 2013 release candidate. Problems with future and packaged_task

#include <future>
#include <iostream>
template<typename T>
void test_moving_packaged_task()
{
    std::packaged_task<T ()> foo;
    std::packaged_task<T ()> foo2 = std::move(foo);

}

int main()
{
    test_moving_packaged_task<int>(); // Compiles
    test_moving_packaged_task<void>(); // Doesn't compile on VS2013
    test_moving_packaged_task<int&>(); // Doesn't compile on VS2013
    std::cout << "This did compile" << std::endl;
}