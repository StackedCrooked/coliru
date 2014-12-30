#include <iostream>
#include <type_traits>
#include <tuple>

using namespace std;

template<typename T>
static void bar(T t) 
{
    cout << "calling bar for " << t << endl;
}

template<typename... Args>
static void foo2(Args... args)
{
    make_tuple( (bar(std::forward<Args>(args)), 0)... );
}

int main()
{
    foo2(1, 2, 3, "3");
    return 0;    
}

