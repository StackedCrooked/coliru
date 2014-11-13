#include <iostream>
#include <vector>
#include <algorithm>

struct Avg {    
    int avg = 0.0;
    unsigned int num = 0;
    
    void operator() (int i) { ++num; avg += i; }
    operator double () { return double (avg) / num; }    
};

int main()
{
    std::vector <int> v {1, 2, 3, 4};
    double d = std::for_each (v.begin (), v.end (), Avg ());
    std::cerr << "Avg = " << d << std::endl;
}
