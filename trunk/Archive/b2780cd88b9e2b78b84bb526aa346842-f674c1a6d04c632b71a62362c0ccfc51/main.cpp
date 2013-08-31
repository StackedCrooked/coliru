#include <iostream>
#include <future>
using namespace std;

template<typename Handler>
void read_cps(Handler h)
{
    h(11);
}

int main()
{
    promise<int> p;
    read_cps([&](int x){ p.set_value(x); });
    cout << p.get_future().get() << endl;
}