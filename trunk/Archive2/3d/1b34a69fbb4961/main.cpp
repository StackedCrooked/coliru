#include <memory>
#include <unordered_map>

struct Bar {};

class Foo {
private:
    std::unordered_map<std::string, std::unique_ptr<Bar>> states;
};

int main() {
    Foo foo;
}