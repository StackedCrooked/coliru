#include <iostream>

template <typename AnArray>
void f(AnArray& array){
    std::cout << sizeof array/sizeof array[0] << std::endl;
}

template <typename AnArray>
void g(AnArray array){
    std::cout << sizeof array/sizeof array[0] << std::endl;
}

int main(){
    int a[] = {1,2,3,4,5};
    f(a);
    g(a);
    return 0;
}
