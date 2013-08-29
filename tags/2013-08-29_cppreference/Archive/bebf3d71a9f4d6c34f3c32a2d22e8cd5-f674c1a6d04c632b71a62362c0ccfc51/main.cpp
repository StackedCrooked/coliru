#include <iostream>
#include <vector>

#pragma pack(push,4)
class Base1 {
  int base1;
};
#pragma pack(pop)

template <typename T> class A : public Base1 {
      T _specialT;
};

int main() {
    /*
     * A: std::vector<int> == 24 bytes (8 alignment)
     * Base1 -> 4 alignment == 4 bytes
     */
    std::cout << "Size of A<std::vector<int>>: " << sizeof(A<std::vector<int>>) << " Bytes" << std::endl;
    std::cout << "Size of Base2: " << sizeof(Base1) << " Bytes" << std::endl;
        
    return 0;    
}