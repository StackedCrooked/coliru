#include <iostream>
#include <bitset>
#include <vector>
#include <array>




class DataClass {
    int data;
public:
    DataClass( int d=0 ) : data(d) {}
    int getData() const { return data; }
};


int main() {
    std::cout << "Hallo Welt\n";
    std::vector<int> ivec01={1,2,3,5,8,13,21};     // C++11
    std::array<int,5> aval={1,2,3,4};
    int i=100;
    std::cin >> i;
    std::cout << i << std::endl;
    
    
}



