#include <iostream>
using namespace std;

template<typename T>
struct F { 
  static T const value;
};

template<> 
struct F<int> { // Specialization
    static int const value; 
}; 

template struct F<int>;

template<typename T>
T const F<T>::value = sizeof(T);

template<>
int const F<int>::value = 42;

int main() {

    struct F<int> ma;
    cout << ma.value;

    return 0;
}