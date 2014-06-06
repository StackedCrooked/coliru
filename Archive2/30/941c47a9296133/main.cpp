template<typename T>
class BasicType {
    T value;
public:
    BasicType() : value(T{}) {};
    BasicType(T v) : value(v) {};
    BasicType &operator=(T v) { value = v; return *this;}
    operator T&() { return value; }
    operator const T&() const { return value; }
};
    
#include <iostream>
int main() {
    using namespace std;
    BasicType<double> d(3.14);
    BasicType<unsigned> u;
    cout << "d = " << d << endl;
    cout << "u = " << u << endl;
    ++u;
    cout << "u = " << u << endl;
    u = 1001;
    d = u;
    cout << "u = " << u << endl;
    cout << "d+u = " << d+u << endl;
}