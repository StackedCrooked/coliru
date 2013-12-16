#include <vector>
#include <utility>

struct X {
    X() = default;
    X(X&& other)
		// move the other.v into this->v, calls std::vector move constructor
		: v(std::move(other.v))
	{
	}
	
	std::vector<int> v;
};

int main()
{
    X x;
    X y(std::move(x)); // move construct 'y' with 'x'
}