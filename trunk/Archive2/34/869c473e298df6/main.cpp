#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
int g_a, g_b;
atomic<int> g_x, g_y;
memory_order lo = memory_order_acquire; //acquire
memory_order so = memory_order_release; //release

void bar1()
{
    int t = 0;
    g_x.store(42, so);
    t = g_y.load(lo);
    g_a = t;
}

void bar2()
{
    int t = 0;
    g_y.store(24, so);
    t = g_x.load(lo);
    g_b = t;
}

int main()
{
    for (int i = 0; i < 1000000; ++i)
    {
        g_a = 0; g_b = 0;
        g_x = 0; g_y =0;

        thread t1(&bar1);
        thread t2(&bar2);

        t1.join();
        t2.join();

        if (g_a == 0 && g_b == 0) cout << "g_a == g_b == 0" << endl;
    }
}
