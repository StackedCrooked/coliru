#include <initializer_list>

template <typename... Ts>
void function(std::initializer_list<Ts>&&... args) {
}

int main() {
    function({1,2,3}, {'h', 'w'}, {"hello", "aloha", "foobarbaz"});
}
