#include <iostream>
#include <string>

// Primary Template
template<typename T> struct ShowType;

// Specialisation for t
#define X(t) template<> struct ShowType<t> { static std::string name() { return #t; }};

// Partial Specialisation for Pointer Types
template<typename T> struct ShowType<T *> {
    static std::string name() { 
        return ShowType<T>::name() + " *";
    }
};

X(bool)
X(char) X(signed char) X(unsigned char)
X(short) X(unsigned short)
X(int)  X(unsigned int)
X(long) X(unsigned long)
X(long long) X(unsigned long long)
X(float) X(double) X(long double)

#include <iostream>
int main() {
 using namespace std;
    auto x = new double();
    
    cout << ShowType<decltype(&x)>::name() << endl;
}

