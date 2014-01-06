#include <iostream>

template <typename T>
class cklasse {};

template <typename T>
using klasse = cklasse<T>;
using kastje = int;

int main() {
    klasse<kastje> mkay;    
}