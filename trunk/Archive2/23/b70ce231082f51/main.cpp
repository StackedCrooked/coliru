#include <iostream>
#include <type_traits>

template<typename T>
auto display(T const& t) -> decltype(t.display(), void())
{
    std::cout << "display(T const& t)\n";
}

void display(int)
{
    std::cout << "display(int)\n";
}

void display(double)
{
    std::cout << "display(double)\n";
}

struct foo
{
    void display() const
    {
        std::cout << "foo::display\n";
    }
};

struct bar {};

int main()
{
    display(10);
    display(10.0);
    display(foo());
//    display(bar()); // doesn't compile
}
