#include <iostream>

template <typename AnArray>
void f(AnArray& array){
    std::cout << sizeof array/sizeof array[0] << std::endl;
}


int main(){
    int a[] = {};
    f(a);
    return 0;
}
