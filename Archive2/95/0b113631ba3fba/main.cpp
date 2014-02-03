#include <iostream>
#include <vector>
#include <functional>

void call_fun_with(std::vector<int> args, std::function<void(int)> fun){
        for(int& arg : args){
            fun(arg);
        }
    }

int main() {
    call_fun_with({0,1,2,3,4}, [](int i){
      std::cout << i << '\n';
    });
    
    return 0;
}