#include <iostream>

class A

{

public:

int sum;

int operator+(int b)

{

return sum+b;

}

};

int main()

{

A a;

a.sum = 10;

std::cout << a+10 << std::endl;

return 0;
}