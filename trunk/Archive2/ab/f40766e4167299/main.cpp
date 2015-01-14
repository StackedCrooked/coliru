#include <string>
#include <utility>

template <typename T> 
struct foo {
    T&& release_contents() { return std::move(contents); } 

  private: 
    T contents; 
};

int main() {
    foo<int> x;
    int y = x.release_contents();
    
    return 0;
}