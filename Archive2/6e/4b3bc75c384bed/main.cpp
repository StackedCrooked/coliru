#include <iostream>
#include <thread>

using std::cout;
using std::thread;

thread_local int a;

void foo()
{
    a = a + 1;
	cout  << a << "\n";
}

void bar()
{
	cout << a << "\n";
}

int main()
{
	thread first(foo);
	thread second(bar);
    second.join();
    first.join();
    cout << a;
}