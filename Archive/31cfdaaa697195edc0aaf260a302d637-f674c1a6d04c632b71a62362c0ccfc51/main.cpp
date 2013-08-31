#include <iostream>

class test_object {
public:
    test_object() { std::cout << "Constructing...\n"; }
    ~test_object() { std::cout << "Destructing...\n"; }
};

void test_function(int count);

int main()
{
    test_function(10);
}

void test_function(int count)
{
    if (!count) return;
    test_object obj;
    test_function(count - 1);
}