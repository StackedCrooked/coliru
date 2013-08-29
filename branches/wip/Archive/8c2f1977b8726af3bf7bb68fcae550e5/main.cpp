#include <limits>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;

//I need to generate a callback to the appropriate function
//paramaters are passed either by value or by const&

void OverloadedFunction(float f) { cout<<f<<endl; }
void OverloadedFunction(const std::string& s) { cout<<s<<endl; }
void OverloadedFunction(float f, const float& g) { cout<<f<<' '<<g<<endl; } //bonus points if this works too

//this works for value parameters (only)
//if I use const Args&, it works for const& parameters (only)
//I need a solution which applies to both

template<typename... Args>
std::function<void()> GenerateCallback(Args... args)
{
    return std::bind((void(*)(Args...))(&OverloadedFunction), args...);
}

int main()
{    
	auto f1 = GenerateCallback(42.f);
    auto f2 = GenerateCallback(std::string("bibi"));
    
    float g = 43.f;
    std::string m("mimi");
    
    auto f3 = GenerateCallback(g);
    auto f4 = GenerateCallback(m);
    
    float h = 44.f;
    
    auto f5 = GenerateCallback(g, h);
    
    f1();
    f2();
    f3();
    f4();
    f5();
}