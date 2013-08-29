#include <utility>

template<class> struct Foo : std::pair<int, int>
{ first_type x; };

int main(){
    Foo<int> f;
}