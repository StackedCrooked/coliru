#include <iostream>

struct Data_T{};

struct X {};

template<typename ...Args>
void execute(Data_T&, Args&...) { std::cout << "variadic\n";}

void execute(Data_T&)  { std::cout << "non variadic\n";}

int main() {
    Data_T d1;
    X x;
    execute(d1, x);
    execute(d1);
}