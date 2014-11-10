#include <iostream>
#include <utility>

void foo(char) { std::cout << "foo(char)\n"; }
template <typename T>
void foo(T&& t) { std::cout << "foo(T&&)\n"; foo(char{std::forward<T>(t)}); }

int main() {
    foo('a');
    // foo(4); // ill-formed
    foo({4});
    // foo(0); // ill-formed
    foo({0}); 
    // foo(u'a'); // ill-formed
    foo({u'a'});
    int i = 2;
    // foo(i); // ill-formed
    // foo({i}); // ill-formed
    (void)i;
}
