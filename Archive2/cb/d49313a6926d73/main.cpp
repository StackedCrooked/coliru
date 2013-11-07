#include <cstdlib>
#include <future>

std::future<int> bar()
{
    
}

std::future<int> baz()
{
	
}
std::future<int> bar();
std::future<int> baz();



int foo(std::future<int>&& future1, std::future<int>&& future2) {
	return (std::rand() % 2 == 0) ? future1.get() : future2.get();
}

int main() {
	foo(bar(), baz());
}
