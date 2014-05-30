#include <iostream>
#include <memory>

template<typename T> struct Array3 {
    Array3(size_t n) : n(n), data(new T[n*n*n]) {}
    
    T &operator() (size_t x, size_t y, size_t z) {
        return data[x + n * (y + n * z)];
    }
    
    const size_t n;
    std::unique_ptr<T[]> data;
};

template<typename T> struct Array3Iterator {
    Array3Iterator(Array3<T> &arr) : arr(arr), x(0), y(0), z(0) {}
    
    Array3Iterator &operator ++() {
        if(++x == arr.n) {
            x = 0;
            if(++y == arr.n) {
                y = 0;
                ++z;
            }
        }
        return *this;
    }
    
    operator bool() const {
        return z < arr.n;
    }
    
    T &operator *() {
        return arr(x, y, z);
    }
    
    Array3<T> &arr;
    size_t x, y, z;
};

int main() {
    Array3<int> arr{2}; // 2*2*2
    for(size_t i = 0; i < arr.n * arr.n * arr.n; ++i) {
        arr.data[i] = i;
    }
    
    for(Array3Iterator<int> iter(arr); iter; ++iter) {
        std::cout << iter.x << ',' << iter.y << ',' << iter.z << ": " << *iter << '\n';
    }
}
