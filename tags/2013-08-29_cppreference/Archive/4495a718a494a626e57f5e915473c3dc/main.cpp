#include <iostream>
#include <tuple>
using namespace std;

class A
{
public:
    template <class First, class... Funcs>
    auto operator()(First first, Funcs... funcs) -> decltype((make_tuple(first(),funcs()...)))
    {
        return (make_tuple(first(),funcs()...)); 
    }
};

int main(){
    auto func1 = [](){ cout << 1 << endl; return 1;};
    auto func2 = [](){ cout << 2 << endl; return 2;};

    A a;
    auto x = a(func1, func2);
    cout << "ans : " << get<0>(x) << get<1>(x) << endl; // I expect ans : 12
}