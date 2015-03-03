#include <string>
#include <iostream>
using namespace std;

void f() { }

// template #1
template<typename T, typename... Args>
void f(T t, Args... args) {
    cout << "in f(T t, Args... args)" << endl;
    f(args...);
}
 //template #2                                                                            
template<typename... Args>
void f(const char* t, Args... args) {
    cout << "in f(const char* t, Args... args)" << endl;
    f(args...);
}
// template #3
template<uint8_t N, typename... Args>
void f(const char (&s)[N], Args... args) {
    cout << "in f(const char (&s)[N], Args... args)" << endl;
    f(args...);
}


int main(){
    int x = 3; f(x); 
f("hello");
const char* p = "world"; f(p);
string s = "stack"; f(s.c_str());
}