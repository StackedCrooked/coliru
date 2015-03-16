#include <iostream>
#include <queue>
#include <deque>

struct foo
{
    foo(int) {}
};

int main()
{
    std::queue<foo> q{std::deque<foo>(10, foo(42))};
    std::cout << q.size() << '\n';
}
