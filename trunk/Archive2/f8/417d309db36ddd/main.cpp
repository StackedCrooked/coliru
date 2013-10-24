#include <iostream>

template<typename T>
void foo(T arg) {
}

template<typename T>
void bar(T arg) {
    typename T::value_type v = *arg++;
}

template<typename T>
void bar(T* arg) {
    T v = *arg++;
}

void bar(int *) {
}

int main() {
    double z;
    foo(z);
    
    bar(std::istream_iterator<double>(cin));
    vector<double> x;
    bar(x.begin());
    bar(&z);
}