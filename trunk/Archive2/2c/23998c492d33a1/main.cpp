#include <iostream>
#include <thread>
#include <cstring>
#include <cassert>

    void swap(std::string& left, char* right) {
      auto right_size = std::strlen(right);
      auto left_size = left.size();
      assert(left_size <= right_size);
      std::string temp = std::move(left);
      left = right;
      std::copy(std::begin(temp), std::end(temp), right);
      right[left_size] = '\0';
    }

    inline void swap(char* left, std::string& right) {
      swap(right, left);
    }

int main() {
    std::string x = "abre-te";
    char y[] = "sesamo,x";
    
    std::cout << x << " // " << y << '\n';
    swap(x, y);
    std::cout << x << " // " << y << '\n';
    swap(x, y);
    std::cout << x << " // " << y << '\n';
    swap(y, x);
    std::cout << x << " // " << y << '\n';
}    