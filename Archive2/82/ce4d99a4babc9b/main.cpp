#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

template<typename T1>
class RREvent1Arg
{
public:
    typedef std::function<void (T1)> Func;

public:
    void Call( T1 arg )
    {
        for( auto& pair : m_handlers )
        {
            pair.second( arg );
        }
    }

    void operator ()(T1 arg)
    {
        Call( arg );
    }

    template<typename Callable>
    RREvent1Arg& operator += ( Callable f )
    {
        m_handlers.emplace(typeid(Callable).name(), f);
        std::cout << "operator+=(" << typeid(Callable).name() << ")\n";
        return *this;
    }

    template<typename Callable>
    RREvent1Arg& operator -= ( Callable f )
    {
        m_handlers.erase(typeid(Callable).name());
        
        return *this;
    }

private:
    std::unordered_map<std::string,Func> m_handlers;
};
void f(int i) {
    
}

int main() {
        
    int stackValue = 200;
    RREvent1Arg<int> e;
    e += f;
    e += [](int i) {};
    
	auto lambda = [&stackValue](int i) { printf( "%d\n", i + stackValue ); };
    e += [=](int i) { printf( "%d\n", i + stackValue ); };
    e += [&](int i) { printf( "%d\n", i + stackValue ); stackValue += 100; };
    e += lambda;
    e += [stackValue](int i) { printf( "%d\n", i + stackValue ); };
    e(100);
	std::cout << "----------------\n";
	e -= lambda;
	e(100);
	
}