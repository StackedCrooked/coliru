#include <iostream>
#include <thread>
#include <cstring>
#include <cassert>

    template<typename Char>
      void swap(std::basic_string<Char>& left, Char* right, std::size_t right_size) {
        auto left_size = left.size();
        assert(left_size <= right_size);
        std::basic_string<Char> temp = std::move(left);
        left = right;
        std::copy(std::begin(temp), std::end(temp), right);
        right[left_size] = '\0';
      }
      
    template<typename Char>
      inline void swap(std::basic_string<Char>& left, Char* right) {
        swap(left, right, std::strlen(right));
      }
      
    template<typename Char>
      inline void swap(Char* left, std::size_t left_size, std::basic_string<Char>& right) {
        swap(right, left, left_size);
      }

    template<typename Char>
      inline void swap(Char* left, std::basic_string<Char>& right) {
        swap(right, left);
      }


int main() {
    std::string x = "abre-te";
    char y[] = "sesamo,x";
    
    std::cout << x << " // " << y << '\n';
    swap(x, y);
    std::cout << x << " // " << y << '\n';
    swap(x, y, sizeof y);
    std::cout << x << " // " << y << '\n';
    swap(y, x);
    std::cout << x << " // " << y << '\n';
    swap(y, sizeof y, x);
    std::cout << x << " // " << y << '\n';
    swap(x, y);
    std::cout << x << " // " << y << '\n';
    swap(y, sizeof y, x);
    std::cout << x << " // " << y << '\n';
}    