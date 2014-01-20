#include <iostream>
#include <string>

template<class T> struct example { void doStuff(); };

template<class T> void example<T>::doStuff() { std::cout<<"default\n"; }

template<> void example<std::string>::doStuff() { std::cout<<"string\n"; }

int main()
{
    example<int>{}.doStuff();
    example<std::string>{}.doStuff();
}