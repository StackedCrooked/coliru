#include <boost/bind.hpp>

void bar(int){ }
void bar(){ }

int main() {
    auto f1 = std::bind(&bar, 42);
    auto f2 = std::bind(&bar);
}
