#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct X1
{
    template<typename... Args>
    X1(Args&&... args)
             : t(std::forward<Args>(args)...) {}

    T t;
};

template<typename T>
struct X2
{
    template<typename... Args>
    X2(Args&&... args)
     : t{std::forward<Args>(args)...} {}

    T t;
};

int main() {
    auto x1 = X1<std::vector<int>> { 42, 2 };
    auto x2 = X2<std::vector<int>> { 42, 2 };
    
    std::cout << "size of X1.t : " << x1.t.size()
              << "\nsize of X2.t : " << x2.t.size();
}