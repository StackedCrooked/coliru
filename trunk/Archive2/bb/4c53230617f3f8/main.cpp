#include <iostream>
#include <vector>
#include <iterator>

void print(int b[]) {
    auto ai = std::end(b)-1;
    std::cout << *ai << '\n';
}
 
int main() 
{
    std::vector<int> v = { 3, 1, 4 };
    auto vi = std::end(v)-1;
    std::cout << *vi << '\n'; 
 
    int a[] = { -5, 10, 15 };
    auto ai = std::end(a)-1;
    
    std::cout << *ai << '\n';
}