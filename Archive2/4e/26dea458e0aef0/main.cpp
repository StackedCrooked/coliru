#include <iostream>
using namespace std;

template<typename... Ts> void show(int, Ts...);
template<typename... Ts> void show(const char *s, Ts...);

void show() {} // necessary to end recursion

template<typename... Ts>
void show(int i, Ts... args) {
    cout << "found integer: " << i << endl;
    show(args...);
}
    
template<typename... Ts>
void show(const char *s, Ts... args) {
    cout << "found cstring: " << '"' << s << '"' << endl;
    show(args...);
}
    
int main() {
    show(123, "hi");
//  show(-1, "lo!");
//  show("hello, world");
//  show(1, 2, "xx");
//  show(1, 2, "xx", 3, 4, "yyy");
}
