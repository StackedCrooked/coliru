#include <string>

using namespace std;

struct S{ 
    string ss; 
    S(string _s):ss{_s} {}
}; 

struct Base{ 
    const char* c; 
    Base(const char* _c):c{_c} {} 
};  

struct Der:S, Base 
{ 
    Der(const char* c):S{c}, Base{ss} {} 
};

int main()
{
    Der d{"foo"};
}