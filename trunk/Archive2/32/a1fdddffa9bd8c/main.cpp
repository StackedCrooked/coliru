#include <iostream>

using namespace std;

template <typename T> struct id{};

void print_type(id<float>) { cout << "float" << endl;}
void print_type(id<int>) { cout << "int" << endl;}

template <typename T, typename U>
auto add(T t, U u) { return t + u; }

int main() {
    auto sum = add(2, 3.0f);
    print_type(id<decltype(sum)>());
}