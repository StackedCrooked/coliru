#include <cstdlib>
#include <functional>

std::function<int(const char *)> f;

int main() {
    f = std::atoi;
    return f("257");
}
