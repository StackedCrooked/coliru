#include <iostream>

int NormalAddingFunction(int x, int y) {
    return x + y;
}

template <typename Function, typename...Args>
auto Presupply(Function function, Args...args) -> decltype(auto) {
    return [=]() {
        return function(args...);
    };
}

template <typename Function>
void PrintFunctionOutput(Function function) {
    std::cout<<function()<<std::endl;
}

int main() {
    auto AddOneAndTwo = Presupply(NormalAddingFunction, 1, 2);
    PrintFunctionOutput(AddOneAndTwo);
}
