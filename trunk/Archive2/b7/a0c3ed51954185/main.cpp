#include <iostream>
#include <functional>

void f( std::function<void()> wo ) // Just ASSUME that i have to use function here.
{
    wo();
}

int main()
{
	int a{}, b{}, c{};
	f( [&]{ std::cout << a << b << c; } );
}
