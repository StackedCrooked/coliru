#include <iostream>
#include <string>
#include <vector>

using namespace std;

class shape {
public:
    shape() { s="shape"; };
    void print(void) { std::cout << s << endl; }
    string s;
};

class circle : public shape {
public:
    circle() : shape() { s="circle"; };
    void print(void) { std::cout << s << endl; }
    string s;
};

int main()
{
shape s();
circle c();
    s.print();
    //c.print();
}
