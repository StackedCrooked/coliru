#include <iostream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

template<class F, class...Ts>
F for_each_arg(F f, Ts&&...a) 
{
    return (void)initializer_list<int>{(ref(f)(forward<Ts>(a)),0)...}, f;
}

int main() 
{
    for_each_arg([](auto p){cout << p << endl;}, 1, 2, "ciao");
}
