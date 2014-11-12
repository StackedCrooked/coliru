#include <vector>
#include <type_traits>
 
template <class T> struct A
{
    typedef std::vector<T> V;
};

template <class T>
using B = typename A<T>::V;

int main() 
{
    B<int> b(10);
}