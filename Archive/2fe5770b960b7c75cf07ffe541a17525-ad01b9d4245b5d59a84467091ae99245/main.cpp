#include <vector>

template<typename T, typename U = std::vector<T>> // fails
void f() {}
 
template<typename T, typename U = std::vector<T>>
class W {}; // compiles?
 

int main()
{
    f<int>();
    W<int>{};
}

