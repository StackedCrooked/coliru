#include <iostream>
#include <vector>
#include <algorithm>


void foo(int x) {
    std::cout << x << "\n";
}


void call_fun_with(std::function<void(int)> fn, std::vector<int> lst) {
    for(auto it : lst)
      fn(it);
}


int main() {
    std::vector<int> val = {1,2,3,4,5};
    
    // c++98
    std::for_each(val.begin(), val.end(), foo);
    
    // c++11
    // vector
    call_fun_with(foo, val);
    
    
    // c++11
    // initializer_list
    int a=0, b=1, c=2;
    call_fun_with(foo, {a,b,c});
}
