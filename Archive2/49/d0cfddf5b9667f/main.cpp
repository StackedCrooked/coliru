#include <iostream>

using namespace std;

template <typename T> struct id{};

void print_type(id<float>) { cout << "float" << endl;}
void print_type(id<float const&>) { cout << "float const&" << endl;}
void print_type(id<int>) { cout << "int" << endl;}

int          func(int) { return 0; }
float const& func(float const& f) { return f; }

int main() {
         float f = 5.0f;
         auto  a = func(5); // int
         auto  b = func(f); // float
decltype(auto) c = func(5); // int
decltype(auto) d = func(f); // float const&

print_type(id<decltype(a)>());
print_type(id<decltype(b)>());
print_type(id<decltype(c)>());
print_type(id<decltype(d)>());
}