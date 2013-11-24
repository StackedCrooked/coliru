#include <initializer_list>

template <typename T>
void function(std::initializer_list<T> il) {
}

int main() {
    function({"hello", "aloha", "foobarbaz"});
}
