#include <memory>

struct foo {};

void somefunc(std::unique_ptr<foo> const&) {}

int main()
{
    std::unique_ptr<foo> p(new foo());
    somefunc(p);
}