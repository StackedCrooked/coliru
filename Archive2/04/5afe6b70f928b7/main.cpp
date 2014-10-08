#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>

using namespace std;

class myvec {
public:
    unsigned int *arr; //pointer to array
    std::size_t n; //size of myvec
public:
myvec() {
    arr = new unsigned int[0];
    n = 0;
}

myvec(std::size_t size) {
    arr = new unsigned int[size];
    n = size;
}

myvec(const myvec& vec) {
    arr = new unsigned int[vec.n];
    n = vec.n;
    for (int i = 0; i < vec.n; i++) {
        arr[i]=vec.arr[i];
    }
}

myvec(std::initializer_list<unsigned int> l) : myvec(l.size()) {
  std::copy(std::begin(l), std::end(l), arr);
}
};

int main()
{
    myvec v = { 1, 2, 3, 4};
    for(int i = 0 ; i < 4 ; ++i)
        std::cout << v.arr[i] << " ";
}
