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

void baz()
{
    cout << "Something\n";
}

int main()
{
	thread first(foo);
	thread second(bar);
    thread third(baz);
    second.join();
    first.join();
    third.join();
    cout << a;
}