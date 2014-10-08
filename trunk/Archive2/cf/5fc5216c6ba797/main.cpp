#include <memory>

class foo
{
public:
    foo(int i) {}
};

int main()
{
    std::unique_ptr<foo> f{new foo{10}};
}