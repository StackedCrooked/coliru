#include <thread>

template<typename T>
struct X
{
    X() : T() { }
    
    X(X&& x) : X(std::unique_lock<std::mutex> l(m), x) 
    { 
    }
    
    X(std::unique_lock<std::mutex> l, X&& x)
        :
        X(std::move(x)
    {
    }
    
    std::mutex m;
    T t;
}

int main()
{
    X<int> x;
}