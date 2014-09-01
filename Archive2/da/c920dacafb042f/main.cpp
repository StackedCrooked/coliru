#include <iostream>
#include <vector>
using namespace std;

template<typename F>
struct array_t
{
    array_t(F f)
        : _f(f)
    {}
    
    auto operator[](size_t i) const
    {
        return _f(i);
    }
    
    F _f;
};

template<typename F>
auto make_subscr(F f)
{
    return array_t<F>{f};
}

template <typename string_t>
void do_something(const string_t& s, size_t n)
{
    for (size_t i=0;i<n;++i)
       std::cout << s[i];    // nota che usa []
}

struct mystr
{
   double x;
   char chr;
};



int main()
{
    std::vector<mystr> v { {1.0, 'A'}, {2.0, 'B'}, {3.0, 'C'} };
    
    do_something( make_subscr([&v](size_t i) { 
        return v[i].chr; }), v.size()) ;

}
