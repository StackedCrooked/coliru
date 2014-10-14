//Number.h
#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>

class Number
{
public:
    Number();
    Number(int ipar);
    Number(const Number& src);
    Number(Number&& src);
public:
    int num;
};

#endif

Number::Number()
{
    std::cout << "default ctor" << std::endl;
}

Number::Number(int ipar) : num(ipar)
{
    std::cout << "integer argument ctor" << std::endl;
}

Number::Number(const Number& src) : num(src.num)
{
    std::cout << "copy ctor" << std::endl;
}

Number::Number(Number&& src) : num(src.num)
{
    std::cout << "move ctor" << std::endl;
}

using namespace std;

int main()
{
    cout << "Part A:" << endl;
    Number n1(1);
    cout << "Part B:" << endl;
    Number n2(n1);
    cout << "Part C:" << endl;
    Number n3{Number{n1}};
    cout << "Part D:" << endl;
    Number n4(Number(n1));
    //n4.num++;
    return 0;
}