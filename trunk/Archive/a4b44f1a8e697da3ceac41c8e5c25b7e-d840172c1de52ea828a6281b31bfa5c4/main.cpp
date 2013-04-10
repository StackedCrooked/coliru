#include <new>
#include <initializer_list>
#include <cstddef>

namespace detail {
template<typename InitList, typename T>
void copy(InitList list, T* array) {
    auto begin = std::begin(list);
    auto end = std::end(list);
    while(begin != end) {
        *array++ = *begin++;
    }
}
} //detail

template<typename T>
class Array {
private:
    size_t arr_size;
    T* data;
public:
    Array(): arr_size(0), data(nullptr) {}
    Array(size_t size) noexcept : arr_size(size), data(new(std::nothrow) T[size]) {}
    Array(std::initializer_list<T> list) {
        arr_size = list.size();
        data = new(std::nothrow) T[arr_size];
        detail::copy(list,data);
    }
    ~Array() {
        delete[] data;
    }

    size_t size() const {
        return arr_size;
    }

    void setSize(size_t size) noexcept {
        arr_size = size;
        data = new(std::nothrow) T[size];
    }

    T operator[](size_t index) const {
        return data[index];
    }

    T& operator[](size_t index) {
        return data[index];
    }

    auto begin() -> decltype(data) {
        return data;
    }

    auto end() -> decltype(data+arr_size) {
        return data+arr_size;
    }
};

#include <iostream>

int main() {
    Array<int> v = {10,20,30,40,50};
    for(auto& i : v) {
        std::cout << i << ' ';
    }
}