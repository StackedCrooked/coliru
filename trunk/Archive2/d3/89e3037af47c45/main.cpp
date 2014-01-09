#include <unordered_map>

using Foo = std::unordered_map<int,int>;

void bar(Foo f = {}) { // using f = Foo{} is okay.
    Foo{std::move(f)};
}

int main() {
    bar({});
}
