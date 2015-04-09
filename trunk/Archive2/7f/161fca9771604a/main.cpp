#include <iostream>
#include <string>
#include <vector>

using namespace std;

class shape {
public:
    shape() { s="shape"; print(); };
    void print(void) { std::cout << s << endl; }
    string s;
};

class circle : public shape {
public:
    circle() : shape() { s="circle"; print(); };
    void print(void) { std::cout << s << endl; }
    string s;
};

int main()
{
shape* s = new shape();
circle* c = new circle();
    s->print();
    c->print();
}
