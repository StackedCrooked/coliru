#include <utility>

class B {
public:
    B() = default;
    B(B &&) = delete;
};

int main() {
    B b0;
    B b1(std::move(b0));
	return 0;
}
