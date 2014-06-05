#include <iostream>
using namespace std;

template<typename... Ts> void show(int, Ts...);
template<typename... Ts> void show(const char *s, Ts...);
void show(int);
void show(const char *);

template<typename... Ts>
void show(int i, Ts... args) {
    cout << "found integer: " << i << endl;
    show(args...);
}
void show(int i) {
    cout << "found last integer: " << i << endl;
}
    
template<typename... Ts>
void show(const char *s, Ts... args) {
    cout << "found cstring: " << '"' << s << '"' << endl;
    show(args...);
}
void show(const char *s) {
    cout << "found last cstring: " << '"' << s << '"' << endl;
}
    
int main() {
//    show(123, "hi");
//  show(-1, "lo!");
//  show("hello, world");
//  show(1, 2, "xx");
    show(1, 2, "xx", 3, 4, "yyy", 444444);
}
