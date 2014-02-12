#include <string>

struct Foo
{
    explicit Foo(std::string s = {}) {}
	//explicit Foo(std::string s = std::string{}) {}
};

int main()
{
	auto x = Foo{};
    (void)x;
	return 0;
}
