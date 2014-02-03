#include <iostream>
#include <vector>
#include <functional>

template<typename FTYPE>
void call_fun_with(FTYPE fun, std::vector<int>& args){
        for(int& arg : args){
            fun(arg);
        }
    }

int main() {
    auto function = [](int i){std::cout << i << '\n';};
    std::vector<int> args;
    args.push_back(0);
    args.push_back(1);
    args.push_back(2);
    args.push_back(3);
    args.push_back(4);
    call_fun_with(function, args);

    return 0;
}