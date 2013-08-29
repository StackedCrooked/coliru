#include <functional>
#include <iostream>
#include <vector>

std::function<void()> li1;

void _li(std::vector<int> __li) {
    li1();
    for ( int ___li : __li)
        std::cout << static_cast<char>(___li);
}

int main() {
    li1=[](){std::cout<<"VALUE IS:";};
    std::function<void(std::vector<int>)> li2 = _li;
    li2({0x46, 0x69, 0x69+1, 0x70-2, 0x70-3,0x61,0x70-2});
    return 0;
}