#include <string>
#include <vector>
#include <iostream>
 
struct T1 {
    int mem1;
    std::string mem2;
}; // no constructors
struct T2 { 
    int mem1;
    std::string mem2;
    T2(const T2&) {} // a constructor, but no default
};
struct T3 { 
    int mem1;
    std::string mem2;
    T3() {} // user-provided default ctor
};
 
std::string s{}; // calls default ctor, the value is "" (empty string)
int main()
{
    int n{};     // non-class value-initialization, value is 0
    double f = double(); // non-class value-init, value is 0.0
    int* a = new int[10](); // array of 10 zeroes
 
    T1 t1{}; // no ctors: zero-initialized
             // t1.mem1 is zero-initialized
             // t1.mem2 is default-initialized
//    T2 t2{}; // error: has a ctor, but no default ctor
    T3 t3{}; // user-defined default ctor:
             // t3.mem1 is default-initialized (the value is indeterminate)
             // t3.mem2 is default-initialized
 
    std::vector<int> v(3); // value-initializes three ints
 
    std::cout << s.size() << ' ' << n << ' ' << f << ' ' << a[9] << ' ' << v[2] << '\n';
    std::cout << t1.mem1 << ' ' << t3.mem1 << '\n';
    delete[] a;
}