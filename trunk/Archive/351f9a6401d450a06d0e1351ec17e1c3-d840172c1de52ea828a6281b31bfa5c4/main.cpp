#include <iostream>

template<typename T, size_t N>
void print(const T(&array)[N]) {
    for(size_t i = 0; i < N; ++i)
        std::cout << array[i] << ' ';
}

template<typename T>
void print(T* t) {
    std::cout << "This shouldn't be called\n";
}

//Just a note, if this was void print(int* t) instead it'd call that instead because decay 2 stronk.

int main() {
    int a[] = {1,2,3,4,5,6};
    print(a);
}