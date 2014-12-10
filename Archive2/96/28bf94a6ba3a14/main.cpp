#include <iostream>
#include <vector>

int main(){
int i1;
std::vector<int> ivec;

while (std::cin >> i1){ ivec.push_back(i1); };

for (int p1 : ivec){
    int i2 = p1 % 2;
    (i2 != 0) ? p1 *= 2 : std::cout << &ivec << " holds an even number";
    i2 = 0;
}   

return 0;
}