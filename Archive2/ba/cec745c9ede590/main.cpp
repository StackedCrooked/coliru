#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

template<bool C, typename T>
struct eenable_if {};

template<typename T>
struct eenable_if<true, T> { using type = T; };

template<bool C, typename T>
using Eenable_if = typename eenable_if<C, T>::type;

int main() {
    Eenable_if<true, double> d = 3.4;
    cout << d << endl;
}