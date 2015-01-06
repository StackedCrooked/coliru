#include <iostream>
#include <thread>

using namespace std;

void task1()
{
    for (int i=0; i<100; i++)
    {
        cout << i << '\n';
    }
}

void task2()
{
    for (int i=0; i<100; i++)
    {
        cout << i << '\n';
    }
}

int main()
{
    thread t1(task1);
    thread t2(task2);
    t1.join();
    t2.join();
    return 0;
}