#include <memory>
#include <iostream>
using namespace std;

template<typename T, void f(T *)>
struct func_deleter {
    void operator()(T *p) const {
        f(p);
    }
};

void mydeleterfunc(int *p) { 
    std::cout << "Sto deletando\n";
    delete p;
}

using my_ptr = std::unique_ptr<int, func_deleter<int, mydeleterfunc>>;

int main()
{
   my_ptr ptr{new int};
   std::cout << sizeof(my_ptr) << "\n"
             << sizeof(std::unique_ptr<int>) << "\n";
}
