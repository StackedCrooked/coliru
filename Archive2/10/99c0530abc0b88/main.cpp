#include <iostream>
#include <sstream>
using namespace std;

struct Vector1
{
    Vector1(int);
    
    friend ostream& operator<<(ostream& os, const Vector1& a)
    {
        os << a.element;
        return os;
    }
private:
    int* element;
    int size;
};

Vector1::Vector1(int a)
{
    element = new int [a];
    for (int i = 0; i < a; i++)
        element[i] = 0;
    a = size;
}

int main()
{
    Vector1 d(10);
    std::cout << d;
}