#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

template<typename Iter, typename Val>
Val sum(Iter first, Iter last) {
    Val s = 0;
    while (first != last) {
        s = s + *first;
        ++first;
    }
    return s;
}

int main() {
    double ad[] = {1,2,3,4};
    double s = sum<double*, double>(ad,ad+4);
}