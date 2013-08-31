#include <iostream>

template<int len>
void func(int (&array)[len]) {
    std::cout << "HI";
}

int main() {
    int array[3] = {};
    func(array); //works, passed array to a function
    int* ptr = array;
    func(ptr); //ERROR POINTER IS NOT AN ARRAY
}