#include <iostream>
#include <string>
#include <vector>

class Foo
{
    Foo& operator=(const Foo&) = delete;
    Foo& operator=(Foo&&) = delete;
};

int main() {
    std::vector<Foo> x;
}