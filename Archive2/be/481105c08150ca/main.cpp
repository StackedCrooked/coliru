#include <vector>

struct T {
public:
    T const& operator=(T const&) const {
        return *this;
    }
};

int main() {
    std::vector<T const> xs;
    xs.emplace_back();
    xs.emplace_back();
    xs.emplace_back();
    return 0;
}