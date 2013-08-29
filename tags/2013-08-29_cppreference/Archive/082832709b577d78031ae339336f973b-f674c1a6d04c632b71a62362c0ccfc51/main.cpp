#include <iostream>

template<class ParamType,class F>
void fun(void* param) {
  F f;
  f(*static_cast<ParamType*>(param));
}

struct my_function {
  void operator()(int& i) {
    std::cout << "got it " << i << std::endl;
  }
};
    
    
int main() {
    void (*func)(void*) = fun<int, my_function>;
    
    int j=4;
    func(&j);
    
    return 0;
}