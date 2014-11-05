#include <functional>
#include <iostream>

class Data {
    public:
        int i;
};

class Compare {
    public:
    bool operator()(int &, Data &) {
        return true;
    }
};
 
template <typename A, typename U = std::less<A>>
bool f(A a, A b, U u = U())
{
    return u(a, b);
}
 
int main() 
{
    Compare comp;
    Data d;
    std::cout << std::boolalpha;   
    std::cout << f(5, d, comp) << '\n';
    std::cout << f(100, 10) << '\n';
}