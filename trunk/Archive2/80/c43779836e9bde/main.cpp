#include <string>
#include <iostream>

using namespace std;

// a C-struct
struct Base{ 
    const char* c; 
};  

struct Der : Base 
{
    const string s;
    Der(string _s) : Base{_s.c_str()}, s{std::move(_s)}  {} 
    
    void Print() { std::cout << c << std::endl; }
};

int main()
{
    Der d{"foo"};
    d.Print();
}