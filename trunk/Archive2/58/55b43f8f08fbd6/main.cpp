#include <boost/bind.hpp>

void bar(int){ }
void bar(){ }

int main() {
    auto f1 = boost::bind(&bar, 42);
    auto f2 = boost::bind(&bar);
}
