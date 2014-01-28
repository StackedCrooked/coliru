#include <string>
#include <utility>
#include <vector>

class foo {
    std::vector<std::string> vec;
public:
	foo(std::vector<std::string> vec): vec{std::move(vec)} {}
};

int main() {
	std::vector<std::string> huge_vec{"foo", "bar", "...", "baz"};
	foo val{std::move(huge_vec)};
}