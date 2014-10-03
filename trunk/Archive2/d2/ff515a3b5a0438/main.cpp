    #include <iostream>
    #include <iomanip>
    #include <bitset>
    
    int main() {
      unsigned int v = 0b00000101; // C++14 binary literal
      
      std::bitset<8> s(v);

      std::cout << s << '\n';
    }