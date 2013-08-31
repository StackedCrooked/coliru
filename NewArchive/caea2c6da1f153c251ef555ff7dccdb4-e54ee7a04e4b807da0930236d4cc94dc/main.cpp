#include<iostream>

class Test
{
public:
    Test() = default;
    void print() const { std::cout << i << "\n"; }
private:
    int i = 42;
};

int main()
{
    Test const t; 
    t.print();
}