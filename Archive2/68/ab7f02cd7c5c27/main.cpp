#include <vector>
#include <iostream>

    template <typename T, std::size_t N>
    struct array
    {
        T _data[N];

        T&       operator[](std::size_t n) noexcept;
        const T& operator[](std::size_t n) const noexcept;

        std::size_t size() const noexcept;

        T* begin() noexcept;
        T* end  () noexcept;

        const T* begin() const noexcept;
        const T* end  () const noexcept;

        T*       data() noexcept;
        const T* data() const noexcept;

        void fill(const T& value) noexcept;
    };
    
    int main() {
        std::vector<array<int, 2>> xs= {{1, 2}, {3, 4}};
        std::cout << "Works";
    }