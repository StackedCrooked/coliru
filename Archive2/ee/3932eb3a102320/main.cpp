#include <iostream>
#include <initializer_list>

void print(std::initializer_list<int> value)
{
    for (auto p = value.begin(); p != value.end(); ++p)
        std::cout << *p << std::endl;
}

class P
{
public:
    P(int, int) { std::cout << "P(int, int)" << std::endl; }
	P(std::initializer_list<int>) { std::cout << "P(initializer_list<>)" << std::endl; }
};

int main()
{
    print({12, 3, 5, 7, 11, 13, 17});

    P p(77, 5);
    P q{77, 5};
    P r{77, 5, 42};
    P s = {77, 5};

    return 0;
}