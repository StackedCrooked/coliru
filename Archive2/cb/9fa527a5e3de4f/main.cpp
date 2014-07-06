#include <iostream>

struct block_scope
{
    block_scope() { std::cout << "block_scope()\n"; }
    ~block_scope() { std::cout << "~block_scope()\n"; }
};

struct sub_object
{
    sub_object() { std::cout << "sub_object()\n"; }
    ~sub_object() { std::cout << "~sub_object()\n"; }
};

sub_object foo()
{
    static block_scope x;
    return {};
}

struct complete_object
{
    sub_object s;
    complete_object() : s(foo())
    { std::cout << "complete_object()\n"; }
    ~complete_object() { std::cout << "~complete_object()\n"; }
};

complete_object c;

int main()
{}