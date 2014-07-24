#include <iostream>
#include <vector>
#include <array>

template <typename T, size_t M, size_t N>
struct vector_storage {
    using type = std::vector<T>;
    
    static type construct() {
        return type(N * M);
    }
};

template <typename T, size_t M, size_t N>
struct array_storage {
    using type = std::array<T, M * N>;
    
    static type construct() {
        return type();
    }
};

template <typename T, std::size_t M, std::size_t N, template<typename, size_t, size_t> class Storage>
struct matrix {
    using storage_type = Storage<T, M, N>;
    
    matrix() : storage(storage_type::construct()) {}
private:
    typename storage_type::type storage;
};

int main() {
    matrix<int, 4, 2, vector_storage> vec_matrix;
    matrix<int, 4, 2, array_storage>  arr_matey;
}